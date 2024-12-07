#ifndef GUIEVENTHANDLER_MOUSEPOSITION_H
#define GUIEVENTHANDLER_MOUSEPOSITION_H

#include <osg/View>
#include <osgEarth/MapNode>
#include <osgGA/GUIEventHandler>
#include <osgEarth/Units>

#include <osgViewer/Viewer>

#include <osgEarthImGui/imgui.h>

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
#include <osgEarth/Style>

using namespace osgEarth;

class GUIEventhandler_MousePosition : public osgGA::GUIEventHandler
{
public:
    GUIEventhandler_MousePosition(osgEarth::MapNode* _mapNode);

	

	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
	
	void setMouseLabel(const GeoPoint& coords, osg::View* view, MapNode* mapNode);

private:
	osgEarth::MapNode* mapNode;

	osg::Group* tempGroup = nullptr;
	osgEarth::Feature* feature = nullptr;
	osgEarth::FeatureNode* featureNode = nullptr;
	osgEarth::Style* geomStyle;

	std::vector<osg::Vec3d> points;

	bool isR = false;

};

#endif // GUIEVENTHANDLER_MOUSEPOSITION_H