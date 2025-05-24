#include "TextViewer.h"
#include "PointMateriel.h"
#include "ChargeElectrique.h"
#include "Systeme.h"

void TextViewer::dessine(const PointMateriel& pm) {
    flot << "Point Matériel :" << std::endl;
    flot << pm << std::endl;
}

void TextViewer::dessine(const ChargeElectrique& ce) {
    flot << "Charge Électrique :" << std::endl;
    flot << ce << std::endl;
}

void TextViewer::dessine(const Systeme& sys) {
    flot << sys;
}