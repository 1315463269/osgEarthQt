#ifndef __MAPORDERMANAGER__
#define __MAPORDERMANAGER__


#include <osgEarth/MapNode>
#include <osgEarth/Threading>
#include <osgEarth/GDAL>
#include <osgEarth/ImageLayer>
#include <osgEarth/TMS>
#include <osgEarth/Map>
#include <osgEarth/Layer>

#include <string>

class MapOrderManager
{
public:
	MapOrderManager();
	~MapOrderManager();

	


private:
	osgEarth::Map* ImageMap;
	osgEarth::Map* EleMap;
	osgEarth::Map* SheMap;

};

#endif //__MAPORDERMANAGER__

