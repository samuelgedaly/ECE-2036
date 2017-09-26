#include <iostream>
#include <cstdlib>
#include <fstream>
#include "PhaseAttr.h"

using namespace std;

PhaseAttributes::PhaseAttributes() {
	this->permittivity = 1;
	this->volumetricFraction = 1;
}
PhaseAttributes::PhaseAttributes(float per, float vf) {
	this->permittivity = per;
	this->volumetricFraction = vf;
}
float PhaseAttributes::getPermittivity() {
	return permittivity;
}
float PhaseAttributes::getVolumetricFraction() {
	return volumetricFraction;
}
PhaseAttributes & PhaseAttributes::setPermittivity(float per) {
	this->permittivity = per;
	return *this;
}
PhaseAttributes & PhaseAttributes::setVolumetricFraction(float vf) {
	this->volumetricFraction = vf;
	return *this;
}
