//This is the geometry file to visualize a thick and thin gedssd detector with a clover array around it. As of now, it sits in the center of the world being built. If it is to be built in conjunciton with GRIFFIN or another detector, the placement will have to be adjusted. More information on the commands can be found below in some comments, and more fully in the README. 

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4PVPlacement.hh"

#include "G4SubtractionSolid.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4AssemblyVolume.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "DetectionSystemGedssd.hh"

#include "G4SystemOfUnits.hh"

#include <string>
//The previous .hh files were all the same ones that were included in Testcan. I will probably leave some of the others down below just in case, and may come back and delete and see if they are necessary after a successful build and visualization. 

#include "Global.hh"
#include "G4Transform3D.hh"
#include "G4UImanager.hh"
#include "G4SDManager.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4RotationMatrix.hh"
#include "G4ios.hh"
#include <sstream>

#include "G4Trd.hh"

DetectionSystemGedssd::DetectionSystemGedssd() :
    //Logical Volumes
    fThickDetectorLog(0),
    fThinDetectorLog(0),
    fThickDetectorCryoLog(0),
    fCryoEndCapLog(0),
    fCloverCrystalLog(0),
    fCloverCryoLog(0)
   
{
    
    //Dimensions for Gedssd
  
    fConvert = 0.0254*m; //Needed to convert inches to meters
    fGeThickDetectorThickness = 1.0*cm; // 2.0cm//Hiro's detector
    fGeThinDetectorThickness = 1.5*mm;
    fGeThickDetectorRadius = 4.5*cm; // 3.0 * cm; //3.0*cm;Hiro's detector
    fGeThinDetectorRadius = 4.5 * cm;
    fGeThickDetectorCryoInnRad = 6.6*cm;
    fGeThickDetectorCryoOutRad = 9.6393*cm;//From Ethan
    fGeThickDetectorCryoThickness = 8.89*cm;//measured with tape measurer
    fGeCryoEndCapOutRad = fGeThickDetectorCryoInnRad;
    fGeCryoEndCapThickness = 1.143*mm; //use 0.1 cm for radioxenon
    fSpacing = 5*mm;
    pi = 3.14159265358979323846;

    //Dimensions for Clover
    CloverCrystalLength = 70.0*mm;
    CloverCrystalRadius = 21.9*mm;
    InnerRadius = 0.*mm;
    CloverCryox = 103.*mm;
    CloverCryoy = 103.*mm;
    CloverCryoz = CloverCrystalLength + 30.0*mm;
     

}
    
DetectionSystemGedssd::~DetectionSystemGedssd() {
     //Deleting logical volumes
     delete fThickDetectorLog;
     delete fThinDetectorLog;
     delete fThickDetectorCryoLog;
     delete fCryoEndCapLog;
     delete fCloverCrystalLog;
     delete fCloverCryoLog;
}

G4int DetectionSystemGedssd::Build() {
    fAssemblyGedssd = new G4AssemblyVolume();
    fAssemblyClover = new G4AssemblyVolume();

    BuildGedssd();

    return 1;

}

G4int DetectionSystemGedssd::PlaceDetector(G4LogicalVolume* expHallLog, G4int detectorNumber) {

    //The constants that will be used in the move functions for the Clover
    G4double x = 0.;
    G4double y = 0.;
    G4double z = CloverCryoz + fGeThickDetectorCryoThickness/2. + 4.715*cm;
    G4double theta = 90.*deg; //degree from z axis

    //Clover 1 commands
    G4double phi1 = 0.*deg; //degree from the x axis. These will increase for each clover placed to go around in a full circle
    G4RotationMatrix* rotate1 = new G4RotationMatrix;
    rotate1->rotateX(90.*deg);
    rotate1->rotateZ(90.*deg);
    G4ThreeVector moveClover1(TransX(x, y, z, theta, phi1), TransY(x, y, z, theta, phi1), TransZ(x, y, z, theta));  

    //Clover 2 commands
    G4double phi2 = 45.*deg;
    G4RotationMatrix* rotate2 = new G4RotationMatrix;
    rotate2->rotateX(90.*deg);
    rotate2->rotateZ(135.*deg);
    G4ThreeVector moveClover2(TransX(x, y, z, theta, phi2), TransY(x, y, z, theta, phi2), TransZ(x, y, z, theta));

    //Clover 3 commands
    G4double phi3 = 90.*deg;
    G4RotationMatrix* rotate3 = new G4RotationMatrix;
    rotate3->rotateX(90.*deg);
    rotate3->rotateZ(0.*deg);
    G4ThreeVector moveClover3(TransX(x, y, z, theta, phi3), TransY(x, y, z, theta, phi3), TransZ(x, y, z, theta));

    //Clover 4 commands
    G4double phi4 = 135.*deg;
    G4RotationMatrix* rotate4 = new G4RotationMatrix;
    rotate4->rotateX(90.*deg);
    rotate4->rotateZ(45.*deg);
    G4ThreeVector moveClover4(TransX(x, y, z, theta, phi4), TransY(x, y, z, theta, phi4), TransZ(x, y, z, theta));

    //Clover 5 commands
    G4double phi5 = 180.*deg;
    G4RotationMatrix* rotate5 = new G4RotationMatrix;
    rotate5->rotateX(90.*deg);
    rotate5->rotateZ(90.*deg);
    G4ThreeVector moveClover5(TransX(x, y, z, theta, phi5), TransY(x, y, z, theta, phi5), TransZ(x, y, z, theta));

    //Clover 6 commands 
    G4double phi6 = 225.*deg;
    G4RotationMatrix* rotate6 = new G4RotationMatrix;
    rotate6->rotateX(90.*deg);
    rotate6->rotateZ(135.*deg);
    G4ThreeVector moveClover6(TransX(x, y, z, theta, phi6), TransY(x, y, z, theta, phi6), TransZ(x, y, z, theta));

    //Clover 7 commands 
    G4double phi7 = 270.*deg;
    G4RotationMatrix* rotate7 = new G4RotationMatrix;
    rotate7->rotateX(90.*deg);
    rotate7->rotateZ(180.*deg);
    G4ThreeVector moveClover7(TransX(x, y, z, theta, phi7), TransY(x, y, z, theta, phi7), TransZ(x, y, z, theta));

    //Clover 8 commands
    G4double phi8 = 315.*deg;
    G4RotationMatrix* rotate8 = new G4RotationMatrix;
    rotate8->rotateX(90.*deg);
    rotate8->rotateZ(45.*deg);
    G4ThreeVector moveClover8(TransX(x, y, z, theta, phi8), TransY(x, y, z, theta, phi8), TransZ(x, y, z, theta));


    //Clover 9 commands
    G4double theta9 = 0.*deg;
    G4double phi9 = 0.*deg;
    G4double z9 = CloverCryoz/2. + fGeThickDetectorCryoThickness/2. + 3.175*cm;
    G4RotationMatrix* rotate9 = new G4RotationMatrix;
    G4ThreeVector moveClover9(TransX(x, y, z9, theta9, phi9), TransY(x, y, z9, theta9, phi9), TransZ(x, y, z9, theta9));

    //Currently, there is a defined number of clovers that will be buit. I will be working on making it so that it can be changed to a certain number of detectors. It may need to be rearraned so that they don't go around in the circle but sort of show up opposite each other. I will come back to this next. 

    for(unsigned int i=1; i<10; i++) {
	
	if(i==1) {
	   rotate = rotate1;
	   move = moveClover1;
	} else if(i==2) {
	   rotate = rotate2;
	   move = moveClover2;
	} else if(i==3) {
	   rotate = rotate3;
	   move = moveClover3;
	} else if(i==4) {
	   rotate = rotate4;
 	   move = moveClover4;
	} else if(i==5) {
	   rotate = rotate5;
	   move = moveClover5;
	} else if(i==6) {
	   rotate = rotate6;
	   move = moveClover6;
	} else if(i==7) {
	   rotate = rotate7;
	   move = moveClover7;
	} else if(i == 8) {
	   rotate = rotate8;
	   move = moveClover8;
	} else if(i==9) {
	   rotate = rotate9;
	   move = moveClover9;
 	}
  
    	fAssemblyClover->MakeImprint(expHallLog, move, rotate); 	
    }

    G4ThreeVector moveNull(0., 0., 0.);

    for(G4int j=1; j<2; j++) {
	move = moveNull;	
	fAssemblyGedssd->MakeImprint(expHallLog, move, rotate);
    }

    return 1;

}

G4int DetectionSystemGedssd::BuildGedssd() {

    G4ThreeVector move, direction;
    G4RotationMatrix* rotate;


    //Materials for the Gedssd
    G4Material* fThinMaterial = G4Material::GetMaterial("Germanium");
    if( !fThinMaterial ) {
	G4cout << "----> Material " << "Germanium" << " not found, cannot build! " << G4endl;
        return 0;
    }

    G4Material* fThickMaterial = G4Material::GetMaterial("Germanium");
    if (!fThickMaterial ) {	
	G4cout << "----> Material " << "Germanium" << " not found, cannot build! " <<G4endl;
	return 0;
    }

    G4Material* fCryoMaterial = G4Material::GetMaterial("Aluminum"); 
    if( !fCryoMaterial ) {
	G4cout << "----> Material Aluminum not found, cannot build! " << G4endl;
	return 0;
    }

    G4Material* fEndCapMaterial = G4Material::GetMaterial("Aluminum");
    if( !fEndCapMaterial ) {
	G4cout << "----> Material Aluminum not found, cannot build! " <<G4endl;
	return 0;
    }


    //Building the Thin Detector
    G4Tubs* ThinDetector = new G4Tubs("GeThinDetector",0.,fGeThinDetectorRadius, fGeThinDetectorThickness/2.,0.,2*pi); 

    //Building the Thick Detector
    G4Tubs* ThickDetector = new G4Tubs("GeThickDetector",0.,fGeThickDetectorRadius, fGeThickDetectorThickness/2.,0.,2*pi);
   
    //Building the Thick Detector Cryo Chamber
    G4Tubs* CryoChamber = new G4Tubs("GeThickDetector",fGeThickDetectorCryoInnRad, fGeThickDetectorCryoOutRad, fGeThickDetectorCryoThickness/2.,0.,2*pi);

    //Building the Cryo End Caps
    G4Tubs* EndCaps = new G4Tubs("GeCryoEndCaps",0.,fGeCryoEndCapOutRad, fGeCryoEndCapThickness/2.,0.,2*pi);


    //The visual attributes for all components 
    G4VisAttributes* ThinDetectorVisAtt = new G4VisAttributes(G4Colour(0.1,0.1,0.1));
    ThinDetectorVisAtt->SetVisibility(true);
    G4VisAttributes* ThickDetectorVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.));
    ThickDetectorVisAtt->SetVisibility(true);
    G4VisAttributes* ThickDetectorCryoVisAtt = new G4VisAttributes(G4Colour::Blue());
    ThickDetectorCryoVisAtt->SetVisibility(true);
    G4VisAttributes* CryoEndCapVisAtt = new G4VisAttributes(G4Colour::Green());
    CryoEndCapVisAtt->SetVisibility(true);
  
    
    //Define the rotation and placement for the thin detector
    thinDirection   =G4ThreeVector(0.,0.,1.);
    thinPosition    =G4ThreeVector(0.,0.,-(fGeThickDetectorThickness/2.)-(fGeThinDetectorThickness/2.)-fSpacing);
    thinRotation      =new G4RotationMatrix; 

    //Define Logical Volume for Thin Detector
    if(fThinDetectorLog == NULL) {
	fThinDetectorLog = new G4LogicalVolume(ThinDetector, fThinMaterial, "GeThinDetector", 0,0,0);
	fThinDetectorLog->SetVisAttributes(ThinDetectorVisAtt);
    }
    fAssemblyGedssd->AddPlacedVolume(fThinDetectorLog, thinPosition, thinRotation);


    //Define rotation and placement for the thick detector
    thickDirection   =G4ThreeVector(0.,0.,1.);
    thickPosition    =G4ThreeVector(0.,0.,0.);
    thickRotation      =new G4RotationMatrix;

    //Define logical volume for thick detector
    if(fThickDetectorLog == NULL) {
	fThickDetectorLog = new G4LogicalVolume(ThickDetector, fThickMaterial, "GeThickDetector",0,0,0);
	fThickDetectorLog->SetVisAttributes(ThickDetectorVisAtt);
    }
    fAssemblyGedssd->AddPlacedVolume(fThickDetectorLog, thickPosition, thickRotation);

    //Define rotation and placement for cryo chamber
    cryoDirection    =G4ThreeVector(0.,0.,1.);
    cryoPosition     =G4ThreeVector(0.,0.,0.);
    cryoRotation     =new G4RotationMatrix;

    //Define logical volume for cryo chamber
    if(fThickDetectorCryoLog == NULL) {
	fThickDetectorCryoLog = new G4LogicalVolume(CryoChamber, fCryoMaterial, "GeThickDetectorCryo", 0,0,0);
	fThickDetectorCryoLog->SetVisAttributes(ThickDetectorCryoVisAtt);
    }
    fAssemblyGedssd->AddPlacedVolume(fThickDetectorCryoLog, cryoPosition, cryoRotation);

    //Define rotation and placement for end caps
    capDirection    =G4ThreeVector(0.,0.,1.);
    cap1Position    =G4ThreeVector(0.,0.,fGeThickDetectorCryoThickness/2. - fGeCryoEndCapThickness/2.);
    cap2Position    =G4ThreeVector(0.,0.,-fGeThickDetectorCryoThickness/2. + fGeCryoEndCapThickness/2.);
    capRotation     =new G4RotationMatrix;

    //Define logical volume for end caps
    if(fCryoEndCapLog == NULL) { 
	fCryoEndCapLog = new G4LogicalVolume(EndCaps, fEndCapMaterial, "GeCryoEndCap", 0,0,0);
	fCryoEndCapLog->SetVisAttributes(CryoEndCapVisAtt);
    }

    fAssemblyGedssd->AddPlacedVolume(fCryoEndCapLog, cap1Position, capRotation);
    fAssemblyGedssd->AddPlacedVolume(fCryoEndCapLog, cap2Position, capRotation);

    //Materials for Clover
    G4Material* fCloverCrystalMaterial = G4Material::GetMaterial("Germanium");
    if( !fCloverCrystalMaterial) {
	G4cout << "----> Material Germanium not found, cannot build!" << G4endl;
	return 0;
    }

    G4Material* fCloverCryoMaterial = G4Material::GetMaterial("Aluminum");
    if( !fCloverCryoMaterial) {
	G4cout << "----> Material Aluminum not found, cannot build!" << G4endl;
	return 0;
    }

    
    //Building the Crystal
    G4Tubs* CloverCrystal = new G4Tubs("CloverCrystal", InnerRadius, CloverCrystalRadius, 35.0*mm, 0., 2*pi);
    
    //Building Cryo Chamber
    G4Box* CloverCryo = new G4Box("CloverCryo", CloverCryox/2., CloverCryoy/2., CloverCryoz/2.);


    //Define visualization attributes
    G4VisAttributes* CloverCrystalVisAtt = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5));
    CloverCrystalVisAtt->SetVisibility(true);
    G4VisAttributes* CloverCryoVisAtt = new G4VisAttributes(G4Colour(0.0, 1.0, 1.0));
    CloverCryoVisAtt->SetVisibility(true);


    //Define placement for crystals
    
    CrystalPosition1 = G4ThreeVector(CloverCrystalRadius, CloverCrystalRadius, 0.);
    CrystalPosition2 = G4ThreeVector(CloverCrystalRadius, -(CloverCrystalRadius), 0.);
    CrystalPosition3 = G4ThreeVector(-(CloverCrystalRadius), -(CloverCrystalRadius), 0.);
    CrystalPosition4 = G4ThreeVector(-(CloverCrystalRadius), CloverCrystalRadius, 0. );
    G4RotationMatrix* crystalRotate = new G4RotationMatrix;

    //Logical volume for Crystals
    if( fCloverCrystalLog == NULL) {
	fCloverCrystalLog = new G4LogicalVolume(CloverCrystal, fCloverCrystalMaterial, "CloverCrystal", 0, 0, 0);
	fCloverCrystalLog->SetVisAttributes(CloverCrystalVisAtt);
    }
    fAssemblyClover->AddPlacedVolume(fCloverCrystalLog, CrystalPosition1, crystalRotate);
    fAssemblyClover->AddPlacedVolume(fCloverCrystalLog, CrystalPosition2, crystalRotate);
    fAssemblyClover->AddPlacedVolume(fCloverCrystalLog, CrystalPosition3, crystalRotate);
    fAssemblyClover->AddPlacedVolume(fCloverCrystalLog, CrystalPosition4, crystalRotate);

    //Define position for cryo chamber
    
    CloverCryoPosition = G4ThreeVector(0., 0., 0.);
    G4RotationMatrix* CloverCryoRotate = new G4RotationMatrix;

    //Logical volume for Cryo chamber
    if( fCloverCryoLog == NULL) {
	fCloverCryoLog = new G4LogicalVolume(CloverCryo, fCloverCryoMaterial, "CloverCry", 0, 0, 0);
	fCloverCryoLog->SetVisAttributes(CloverCryoVisAtt);
    }
    fAssemblyClover->AddPlacedVolume(fCloverCryoLog, CloverCryoPosition, CloverCryoRotate);


    return 1;
} 


