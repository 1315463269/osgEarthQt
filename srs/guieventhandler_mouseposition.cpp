#include "guieventhandler_mouseposition.h"
#include <QDebug>




GUIEventhandler_MousePosition::GUIEventhandler_MousePosition(osgEarth::MapNode* _mapNode)
{
	mapNode = _mapNode;
}

bool GUIEventhandler_MousePosition::handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter & aa)
{
	osgViewer::Viewer *viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
	if (viewer)
	{
		/*if (ea.getEventType() == osgGA::GUIEventAdapter::FRAME)
			return false;
		if (ea.getKey() == osgGA::GUIEventAdapter::KEY_C)
		{
			isR = !isR;
			
		}

		if (!isR)
		{
			return false;
		}*/

		if (ea.getEventType() == osgGA::GUIEventAdapter::MOVE )
		{
			osg::Vec3d world;
			if (mapNode->getTerrain()->getWorldCoordsUnderMouse(aa.asView(), ea.getX(), ea.getY(), world));
			{
				osgEarth::GeoPoint map;
				map.fromWorld(mapNode->getMapSRS(), world);
				/*qDebug() << "x: " << world.x() << ", y: " << world.y() << ", z: " << world.z();
				qDebug() << "x: " << map.x() << ", y: " << map.y() << ", z: " << map.z();*/
				/*auto mp = dynamic_cast<osgEarth::Util::EarthManipulator*>(viewer->getCameraManipulator());
				auto vieport = mp->getViewpoint();*/

				if (points.size() >= 2)
				{
					osg::Vec3d tempPoint(map.x(), map.y(), map.z());
					if (feature == nullptr)
					{
						Geometry* geoMery = new osgEarth::Polygon();
						for (int i = 0; i < points.size(); i++)
						{
							geoMery->push_back(points[i]);
						}
						geoMery->push_back(tempPoint);
						feature = new Feature(geoMery, mapNode->getMapSRS()->getGeographicSRS());

						geomStyle = new osgEarth::Style;
						geomStyle->getOrCreate<PolygonSymbol>()->fill()->color() = Color(Color::Green, 0.8);
						geomStyle->getOrCreate<LineSymbol>()->stroke()->smooth() = true;
						geomStyle->getOrCreate<osgEarth::AltitudeSymbol>()->clamping() = osgEarth::AltitudeSymbol::CLAMP_TO_TERRAIN;
						geomStyle->getOrCreate<osgEarth::AltitudeSymbol>()->technique() = osgEarth::AltitudeSymbol::TECHNIQUE_DRAPE;

						featureNode = new FeatureNode(feature, *geomStyle);

						tempGroup = new osg::Group;
						mapNode->addChild(tempGroup);
						tempGroup->addChild(featureNode);
					}
					else
					{
						feature->getGeometry()->pop_back();
						feature->getGeometry()->push_back(tempPoint);
						featureNode->dirty();
					}
				}
				
			}
		}
		else if (ea.getEventType() == osgGA::GUIEventAdapter::RELEASE && ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
		{
			osg::Vec3d world;
			osg::Vec3d mousePos;
			if (mapNode->getTerrain()->getWorldCoordsUnderMouse(aa.asView(), ea.getX(), ea.getY(), world));
			{
				osgEarth::GeoPoint map;
				map.fromWorld(mapNode->getMapSRS(), world);
				mousePos.set(map.x(), map.y(), map.z());
				points.push_back(mousePos);
			}
			if (points.size() >= 3)
			{
				if (feature == nullptr)
				{
					Geometry* geoMery = new osgEarth::Polygon();
					for (int i = 0; i < points.size(); i++)
					{
						geoMery->push_back(points[i]);
					}
					feature = new Feature(geoMery, mapNode->getMapSRS()->getGeographicSRS());

					geomStyle = new osgEarth::Style;
					geomStyle->getOrCreate<PolygonSymbol>()->fill()->color() = Color(Color::Green, 0.8);
					geomStyle->getOrCreate<LineSymbol>()->stroke()->smooth() = true;
					geomStyle->getOrCreate<osgEarth::AltitudeSymbol>()->clamping() = osgEarth::AltitudeSymbol::CLAMP_TO_TERRAIN;
					geomStyle->getOrCreate<osgEarth::AltitudeSymbol>()->technique() = osgEarth::AltitudeSymbol::TECHNIQUE_DRAPE;

					featureNode = new FeatureNode(feature, *geomStyle);

					tempGroup = new osg::Group;
					mapNode->addChild(tempGroup);
					tempGroup->addChild(featureNode);

				}
				else
				{
					feature->getGeometry()->pop_back();
					feature->getGeometry()->push_back(mousePos);
					//feature->getGeometry()->push_back(mousePos);
					featureNode->dirty();
				}
			}
		}
		else if (ea.getEventType() == osgGA::GUIEventAdapter::RELEASE && ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
		{
			points.clear();
			if (feature != nullptr)
			{
				feature = nullptr;
				tempGroup->removeChild(featureNode);
				mapNode->removeChild(tempGroup);
				tempGroup = nullptr;
				featureNode = nullptr;
			}

		}
	}
	return false;
}
