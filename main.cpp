#include <iostream>


#include "ogrsf_frmts.h"

int main() {
    OGRRegisterAll();

    OGRDataSource*poDS;

    poDS = OGRSFDriverRegistrar::Open("world-continents.shp", FALSE);
    if (poDS == nullptr) {
        printf("Open failed.\n");
        exit(1);
    }

    std::cout << "Hello, World!" << std::endl;

    for (int i = 0; i < poDS->GetLayerCount(); ++i) {
        std::cout << poDS->GetLayer(i)->GetName() << std::endl;
    }

    OGRLayer*poLayer;
    poLayer = poDS->GetLayerByName("world-continents");

    OGRFeature*poFeature;

    poLayer->ResetReading();
    while ((poFeature = poLayer->GetNextFeature()) != nullptr) {
        auto geom = dynamic_cast<OGRMultiPolygon*>(poFeature->GetGeometryRef());
        std::cout << "FID " << poFeature->GetFieldAsString(0) << std::endl;

        for (int i = 0; i < geom->getNumGeometries(); i++) {
            auto ref = dynamic_cast<OGRPolygon*>(geom->getGeometryRef(i));
            std::cout << "\tgeom_type " << geom->getGeometryName() << " " << geom->getGeometryType() << std::endl;

            auto ring = ref->getExteriorRing();
            for (int p = 0; p < ring->getNumPoints(); ++p) {
                auto pt = std::make_shared<OGRPoint>();
                ring->getPoint(p, pt.get());

                std::cout << "\t\tx:" << pt->getX() << "\ty:" << pt->getY() << std::endl;
            }
        }
    }

    return 0;
}
