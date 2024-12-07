#include "mainwindow_osgearth.h"
#include <QApplication>

#include <osgQOpenGL/osgQOpenGLWidget>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osg/CoordinateSystemNode>
#include <osg/Switch>
#include <osg/Types>
#include <osgText/Text>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/TerrainManipulator>
#include <osgGA/SphericalManipulator>
#include <osgGA/Device>
#include <QSurfaceFormat>
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;

//osgEarth
#include <osgViewer/Viewer>
#include <osgEarth/Notify>
#include <osgEarth/EarthManipulator>
#include <osgEarth/ExampleResources>
#include <osgEarth/MapNode>
#include <osgEarth/Threading>
#include <osgEarth/GDAL>
#include <osgEarth/ImageLayer>
#include <osgEarth/TMS>
//using namespace osgEarth;
//using namespace osgEarth::Util;

#include <osgEarth/Metrics>
#include <osgEarthImGui/imgui.h>
#include <osgEarthImGui/imgui_impl_opengl3.h>
#include <osgEarthImGui/ImGuiApp>
#include <osgEarthImGui/ViewpointsGUI>

#include <osgEarth/Bounds>

#include <osgEarth/PolygonSymbol>
#include <osgEarth/Feature>
#include <osgEarth/FeatureNode>
#include <osgEarth/TrackNode>

#include <osgEarth/CircleNode>
#include <osgEarth/RectangleNode>
#include <osgEarth/EllipseNode>
#include <osgEarth/PlaceNode>
#include <osgEarth/LabelNode>
#include <osgEarth/Geometry>

#include "guieventhandler_mouseposition.h"

#include <QDebug>


osg::ref_ptr<osg::Node>DrawRange(const osgEarth::SpatialReference* mapSRS)
{
	Geometry* geom = new osgEarth::Polygon();
	geom->push_back(osg::Vec3d(121.981, 39.6017, 170));
	geom->push_back(osg::Vec3d(121.985, 39.6018, 122));
	geom->push_back(osg::Vec3d(121.985, 39.5934, 95.9188));
	geom->push_back(osg::Vec3d(121.977, 39.5955, 223));

	
	Feature* feature = new Feature(geom, mapSRS);
	feature->geoInterp() = GEOINTERP_RHUMB_LINE;

	
	Style geomStyle;
	//geomStyle.getOrCreate<RenderSymbol>()->depthOffset().mutable_value().enabled() = true;
	geomStyle.getOrCreate<PolygonSymbol>()->fill()->color() = Color(Color::White, 0.8);
	geomStyle.getOrCreate<LineSymbol>()->stroke()->smooth() = true;
	geomStyle.getOrCreate<osgEarth::AltitudeSymbol>()->clamping() = osgEarth::AltitudeSymbol::CLAMP_TO_TERRAIN;
	geomStyle.getOrCreate<osgEarth::AltitudeSymbol>()->technique() = osgEarth::AltitudeSymbol::TECHNIQUE_DRAPE;

	FeatureNode* fnode = new FeatureNode(feature, geomStyle);

	

	return fnode;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    osgEarth::initialize();
	osg::ArgumentParser arguments(&argc, argv);
	osgQOpenGLWidget widget(&arguments);
	QObject::connect(&widget, &osgQOpenGLWidget::initialized, [&arguments, &widget]
	{
		osgEarth::Util::EarthManipulator* mp = new osgEarth::Util::EarthManipulator(arguments);
		widget.getOsgViewer()->setCameraManipulator(mp);
		widget.getOsgViewer()->getCamera()->setSmallFeatureCullingPixelSize(-1.0f);
		string tifFile = "E:/map/world.tif";
		osg::ref_ptr<osgEarth::Map> rp_Map = new osgEarth::Map;
		osg::ref_ptr<osgEarth::GDALImageLayer> rp_GDALImageLayer = new  osgEarth::GDALImageLayer;
		rp_GDALImageLayer->setURL(osgEarth::URI(tifFile));
		
		osg::ref_ptr<osgEarth::TMSImageLayer> rp_tmsImageLayer = new osgEarth::TMSImageLayer;
		rp_tmsImageLayer->setURL(osgEarth::URI("E:/map/bandao/tms.xml"));

		osg::ref_ptr<osgEarth::GDALElevationLayer> rp_GDALElevationLayer = new osgEarth::GDALElevationLayer;
		rp_GDALElevationLayer->setURL(osgEarth::URI("E:/map/bandao/dem.tif"));

		osg::ref_ptr<osgEarth::GDALElevationLayer> rp_GDALElevationLayerW = new osgEarth::GDALElevationLayer;
		rp_GDALElevationLayerW->setURL(osgEarth::URI("E:/map/bandao/mt_everest_90m.tif"));

		osg::ref_ptr<osgEarth::MapNode> rp_rootNode = new osgEarth::MapNode(rp_Map.get());
		

		/*osg::ref_ptr<osgEarth::GDALImageLayer> rp_GDALImageLayer18 = new  osgEarth::GDALImageLayer;
		rp_GDALImageLayer18->setURL(osgEarth::URI("E:/map/bandao/16.tif"));*/

		
		rp_Map->addLayer(rp_GDALImageLayer.get());
		rp_Map->addLayer(rp_tmsImageLayer.get());
		rp_Map->addLayer(rp_GDALElevationLayerW.get());
		rp_Map->addLayer(rp_GDALElevationLayer.get());
		//rp_Map->addLayer(rp_GDALImageLayer18.get());
		
		std::string str = rp_GDALImageLayer->getProfile()->toString();
		qDebug() << "str: " << QString::fromStdString(str);
		
		/*DataExtentList dataExtents_;
		rp_GDALElevationLayer->getDataExtents(dataExtents_);
		osgEarth::Bounds bound = dataExtents_.data()->bounds();
		double x = bound.center().x();
		double y = bound.center().y();
		osgEarth::Viewpoint* vp = new osgEarth::Viewpoint("1", 45.0, 45.0, 0.0, 0, -90, 20000000);*/
		
		

		//loc to ImageLayer
		

		/*auto ui = new osgEarth::Util::ImGuiAppEngine();
		ui->add("Tools", new osgEarth::Util::ViewpointsGUI());
		widget.getOsgViewer()->getEventHandlers().push_front(ui);*/
		auto anNode = DrawRange(rp_rootNode->getMapSRS()->getGeographicSRS());
		
		osg::Group* lablGroup = new osg::Group();
		rp_rootNode->addChild(lablGroup);
		lablGroup->addChild(anNode);
		

		widget.getOsgViewer()->addEventHandler(new GUIEventhandler_MousePosition(rp_rootNode.get()));
		widget.getOsgViewer()->setSceneData(rp_rootNode.get());
		auto vieport = mp->getViewpoint();
		widget.setFocus();
		widget.setMouseTracking(true);
		return 0;

	});

    MainWindow_osgEarth w;
	w.resize(QSize(1920, 1600));
	w.setCentralWidget(&widget);
    w.show();

    return a.exec();
}
