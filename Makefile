CC = $(CXX)
CXXFLAGS = -std=c++17
CXXFLAGS += -pedantic -Wall -Wextra -Werror
CXXFLAGS += -g

.PHONY: all clean

all: testVecteur testIntegrateur1 testPointMateriel testPomme exerciceP9-pomme exerciceP11-magnetique

GravitationConstante.o: ChampForces.h GravitationConstante.cc GravitationConstante.h ObjetPhysique.h Vecteur.h constantes.h
	$(CXX) $(CXXFLAGS) -c GravitationConstante.cc

Libre.o: Contrainte.h Libre.cc Libre.h ObjetPhysique.h Vecteur.h
	$(CXX) $(CXXFLAGS) -c Libre.cc

testVecteur.o: Vecteur.h testVecteur.cc
	$(CXX) $(CXXFLAGS) -c testVecteur.cc

ChargeElectrique.o: ChampForces.h ChargeElectrique.cc ChargeElectrique.h Contrainte.h Dessinable.h ObjetPhysique.h SupportADessin.h Vecteur.h
	$(CXX) $(CXXFLAGS) -c ChargeElectrique.cc

IntegrateurEulerCromer.o: Integrateur.h IntegrateurEulerCromer.cc IntegrateurEulerCromer.h ObjetMobile.h Vecteur.h
	$(CXX) $(CXXFLAGS) -c IntegrateurEulerCromer.cc

exercice9.o: GravitationConstante.h IntegrateurEulerCromer.h Libre.h PointMateriel.h Systeme.h TextViewer.h exercice9.cc
	$(CXX) $(CXXFLAGS) -c exercice9.cc

Systeme.o: ChampForces.h ChampNewtonien.h ChargeElectrique.h Contrainte.h Dessinable.h GravitationConstante.h Integrateur.h IntegrateurEulerCromer.h Libre.h ObjetPhysique.h PointMateriel.h SupportADessin.h Systeme.cc Systeme.h
	$(CXX) $(CXXFLAGS) -c Systeme.cc

IntegrateurRungeKutta4.o: Integrateur.h IntegrateurRungeKutta4.cc IntegrateurRungeKutta4.h ObjetMobile.h
	$(CXX) $(CXXFLAGS) -c IntegrateurRungeKutta4.cc

ForceCentrale.o: ChampForces.h ForceCentrale.cc ForceCentrale.h ObjetPhysique.h Vecteur.h
	$(CXX) $(CXXFLAGS) -c ForceCentrale.cc

ObjetMobile.o: ObjetMobile.cc ObjetMobile.h Vecteur.h
	$(CXX) $(CXXFLAGS) -c ObjetMobile.cc

ChampNewtonien.o: ChampNewtonien.cc ChampNewtonien.h ForceCentrale.h ObjetPhysique.h Vecteur.h
	$(CXX) $(CXXFLAGS) -c ChampNewtonien.cc

ObjetPhysique.o: ChampForces.h Contrainte.h ObjetMobile.h ObjetPhysique.cc ObjetPhysique.h
	$(CXX) $(CXXFLAGS) -c ObjetPhysique.cc

testPointMateriel.o: GravitationConstante.h Libre.h PointMateriel.h Vecteur.h testPointMateriel.cc
	$(CXX) $(CXXFLAGS) -c testPointMateriel.cc

testIntegrateur1.o: GravitationConstante.h IntegrateurEulerCromer.h Libre.h PointMateriel.h testIntegrateur1.cc
	$(CXX) $(CXXFLAGS) -c testIntegrateur1.cc

PointMateriel.o: ChampForces.h Contrainte.h Dessinable.h ObjetPhysique.h PointMateriel.cc PointMateriel.h SupportADessin.h Vecteur.h
	$(CXX) $(CXXFLAGS) -c PointMateriel.cc

TextViewer.o: ChargeElectrique.h PointMateriel.h SupportADessin.h Systeme.h TextViewer.cc TextViewer.h
	$(CXX) $(CXXFLAGS) -c TextViewer.cc

testPomme.o: ChampNewtonien.h IntegrateurEulerCromer.h Libre.h PointMateriel.h testPomme.cc
	$(CXX) $(CXXFLAGS) -c testPomme.cc

exerciceP9-pomme.o: Systeme.h PointMateriel.h ChampNewtonien.h Libre.h IntegrateurEulerCromer.h TextViewer.h exerciceP9-pomme.cc
	$(CXX) $(CXXFLAGS) -c exerciceP9-pomme.cc

exerciceP9-pomme: exerciceP9-pomme.o PointMateriel.o Libre.o Vecteur.o ObjetMobile.o ObjetPhysique.o ChampNewtonien.o IntegrateurEulerCromer.o ForceCentrale.o Systeme.o TextViewer.o ChargeElectrique.o GravitationConstante.o
	$(CXX) -o exerciceP9-pomme exerciceP9-pomme.o PointMateriel.o Libre.o Vecteur.o ObjetMobile.o ObjetPhysique.o ChampNewtonien.o IntegrateurEulerCromer.o ForceCentrale.o Systeme.o TextViewer.o ChargeElectrique.o GravitationConstante.o

Vecteur.o: Vecteur.cc Vecteur.h
	$(CXX) $(CXXFLAGS) -c Vecteur.cc

testSysteme.o: ChampNewtonien.h IntegrateurEulerCromer.h Libre.h PointMateriel.h Systeme.h testSysteme.cc
	$(CXX) $(CXXFLAGS) -c testSysteme.cc

testVecteur: testVecteur.o Vecteur.o
	$(CXX) -o testVecteur testVecteur.o Vecteur.o

testIntegrateur1: testIntegrateur1.o PointMateriel.o Vecteur.o ObjetMobile.o ObjetPhysique.o GravitationConstante.o IntegrateurEulerCromer.o Libre.o
	$(CXX) -o testIntegrateur1 testIntegrateur1.o PointMateriel.o Vecteur.o ObjetMobile.o ObjetPhysique.o GravitationConstante.o IntegrateurEulerCromer.o Libre.o

testPointMateriel: testPointMateriel.o PointMateriel.o Libre.o Vecteur.o ObjetMobile.o ObjetPhysique.o GravitationConstante.o IntegrateurEulerCromer.o TextViewer.o Systeme.o ChargeElectrique.o ChampNewtonien.o ForceCentrale.o
	$(CXX) -o testPointMateriel testPointMateriel.o PointMateriel.o Libre.o Vecteur.o ObjetMobile.o ObjetPhysique.o GravitationConstante.o IntegrateurEulerCromer.o TextViewer.o Systeme.o ChargeElectrique.o ChampNewtonien.o ForceCentrale.o

testPomme: testPomme.o PointMateriel.o Libre.o Vecteur.o ObjetMobile.o ObjetPhysique.o ChampNewtonien.o IntegrateurEulerCromer.o ForceCentrale.o 
	$(CXX) -o testPomme testPomme.o PointMateriel.o Libre.o Vecteur.o ObjetMobile.o ObjetPhysique.o ChampNewtonien.o IntegrateurEulerCromer.o ForceCentrale.o 

ChampElectromagnetique.o: ChampElectromagnetique.cc ChampElectromagnetique.h ChampForces.h ChargeElectrique.h ObjetPhysique.h Vecteur.h
	$(CXX) $(CXXFLAGS) -c ChampElectromagnetique.cc

ChampCompose.o: ChampCompose.cc ChampCompose.h ChampForces.h ObjetPhysique.h
	$(CXX) $(CXXFLAGS) -c ChampCompose.cc

FrottementFluide.o: FrottementFluide.cc FrottementFluide.h ChampForces.h ObjetPhysique.h Vecteur.h
	$(CXX) $(CXXFLAGS) -c FrottementFluide.cc

exerciceP11-magnetique.o: exerciceP11-magnetique.cc ChampCompose.h ChampElectromagnetique.h ChargeElectrique.h FrottementFluide.h IntegrateurEulerCromer.h Libre.h Systeme.h TextViewer.h
	$(CXX) $(CXXFLAGS) -c exerciceP11-magnetique.cc

exerciceP11-magnetique: exerciceP11-magnetique.o PointMateriel.o Libre.o Vecteur.o ObjetMobile.o ObjetPhysique.o ChampElectromagnetique.o ChampCompose.o FrottementFluide.o IntegrateurEulerCromer.o Systeme.o TextViewer.o ChargeElectrique.o ChampNewtonien.o GravitationConstante.o ForceCentrale.o
	$(CXX) -o exerciceP11-magnetique exerciceP11-magnetique.o PointMateriel.o Libre.o Vecteur.o ObjetMobile.o ObjetPhysique.o ChampElectromagnetique.o ChampCompose.o FrottementFluide.o IntegrateurEulerCromer.o Systeme.o TextViewer.o ChargeElectrique.o ChampNewtonien.o GravitationConstante.o ForceCentrale.o

clean:
	rm -f *.o testVecteur testIntegrateur1 testPointMateriel testPomme exerciceP9-pomme exerciceP11-magnetique
