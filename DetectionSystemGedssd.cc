//This is the 3rd draft of the DetectionSystemGedssd file. The previous attempts would not build or would not visualize the geometry. The file is being rewritten to model the Testcan file. The first and second drafts can be found in ~/geant/New Files

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
    //These were necessary to add in order to actually build the detector. The functions are defiend below and were modeled after Joey Turko's files for Testcan.
    fThickDetectorLog(0),
    fThinDetectorLog(0),
    fThickDetectorCryoLog(0),
    fCryoEndCapLog(0),
    fCloverCrystalLog(0),
    fCloverCryoLog(0)
   
{
    
    //Some parameters and dimensions for the Gedssd
  
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

    //Extra parametersa nd dimensions for the clover
    CloverCrystalLength = 70.0*mm;
    CloverCrystalRadius = 21.9*mm;
    InnerRadius = 0.*mm;
    CloverCryox = 103.*mm;
    CloverCryoy = 103.*mm;
    CloverCryoz = CloverCrystalLength + 30.0*mm;
     

}
    
DetectionSystemGedssd::~DetectionSystemGedssd() {
     //LogicalVolumes
     delete fThickDetectorLog;
     delete fThinDetectorLog;
     delete fThickDetectorCryoLog;
     delete fCryoEndCapLog;
     delete fCloverCrystalLog;
     delete fCloverCryoLog;
}

//In the original file, the parts were all constructed differently. For this go, since I am trying to mimic the structure of Testcan, I will put them all in one construction function and see how that goes. I have the old structure saved as indicted in the heading of the file. 

G4int DetectionSystemGedssd::Build() {
    fAssemblyGedssd = new G4AssemblyVolume();
    fAssemblyClover = new G4AssemblyVolume();

    BuildGedssd();

    return 1;

}
//The PlaceDetector function had to be added in order to actually tell the messenger to place the detector once it was built. Otherwise, it would not show up. Some issues curretnly with it showing an error when tyring to build. I have tried it with and without the G4int detectorNumber. Neither is fixing the problem where it says it is not a static member of the class. 
G4int DetectionSystemGedssd::PlaceDetector(G4LogicalVolume* expHallLog, G4int detectorNumber) {

    G4RotationMatrix* rotate = new G4RotationMatrix;
    G4ThreeVector move = G4ThreeVector(0., 0., 0.);

    //(6/21/17) I am going to need a separate for loop for the two assembly volumes, since I need different numbers of them. I will need 9 clovers and only one gedssd. This means that I will need to try and orient the clovers around the central gedssd, but I am going to start with making sure I have the measurements right for just one of them, and then I can begin rotating and adding more. I will be referecning Descant to see how they handle the moving and rotating in this PlaceDetector function.
    //So Sceptar defines their move functions outside of the for loop then calls them all move later one in order ot only have to do the MakeImprint function once. I will try doing this. 
    G4double fCloverRotate = 10.*deg;    

    G4RotationMatrix* rotateClover1 = new G4RotationMatrix;
    rotateClover1->rotateX(90.*deg);
    rotateClover1->rotateY(45.*deg);
    rotateClover1->rotateY(180.*deg);
    G4ThreeVector moveClover1(-(CloverCryox/2. + 2.1*cm), CloverCryoy/2. + 2.1*cm, CloverCryoz/2. + fGeThickDetectorThickness/2. + 2.175*cm);

    G4RotationMatrix* rotateClover2 = new G4RotationMatrix;
    rotateClover2->rotateX(90.*deg);
    rotateClover2->rotateY(45.*deg);
    rotateClover2->rotateY(180.*deg);
    G4ThreeVector moveClover2(CloverCryox/2. + 2.1*cm, -(CloverCryoy/2. + 2.1*cm), CloverCryoz/2. + fGeThickDetectorThickness/2. + 4.715*cm);

    for(G4int i=0; i<2; i++) {
	
	if(i==0) {
	   rotate = rotateClover1;
	   move = moveClover1;
	   move.rotateZ(10.*deg);
	   rotate->rotateZ(10.*deg);
	} else if(i==1) {
	   rotate = rotateClover2;
	   move = moveClover2;
	   move.rotateZ(10.*deg);
	   rotate->rotateZ(10.*deg);
	}
  
    	fAssemblyClover->MakeImprint(expHallLog, move, rotate); 	
    }

    for(G4int j=1; j<2; j++) {
	
	fAssemblyGedssd->MakeImprint(expHallLog, move, rotate);
    }

    return 1;

}

G4int DetectionSystemGedssd::BuildGedssd() {

    G4ThreeVector move, direction;
    G4RotationMatrix* rotate;


    //First, I will define all of the materials necessary for the parts
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
    //He has a cut and a cutting volume, but I don't think that applies to this geometry, so I am going to leave it out for now, may have to ask Joey about it once he gets back to me.
    G4Tubs* ThinDetector = new G4Tubs("GeThinDetector",0.,fGeThinDetectorRadius, fGeThinDetectorThickness/2.,0.,2*pi); 
    
    //The below were I think just related to the subtraction solid that Joey had. I will leave commented out for now. However, not sure where I should put the position stuff that I have defined in the last file. I think that might be the move he has following the building of the detectors
    //move = G4ThreeVector(0.,0.,-(fGeThickDetectorThickness/2.)-(fGeThinDetectorThickness/2.)-fSpacing);
    //rotate = new G4RotationMatrix;
    //Here Joey has a subtraction solid. I'm not quite sure what that is for so I am going to try and do it without.

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

    //Now I will do the building for the Clover
    
    //Define materials, then solids, then rotation and placement, then logical volumes. 

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

    //Define the solid objects
    
    G4Tubs* CloverCrystal = new G4Tubs("CloverCrystal", InnerRadius, CloverCrystalRadius, 35.0*mm, 0., 2*pi);
    G4Box* CloverCryo = new G4Box("CloverCryo", CloverCryox/2., CloverCryoy/2., CloverCryoz/2.);

    //Define visualization attributes
    
    G4VisAttributes* CloverCrystalVisAtt = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5));
    CloverCrystalVisAtt->SetVisibility(true);
    G4VisAttributes* CloverCryoVisAtt = new G4VisAttributes(G4Colour(0.0, 1.0, 1.0));
    CloverCryoVisAtt->SetVisibility(true);

    //Define rotation and placement for crystals
    //There are 4 different positions that the clovers will be in, so define all of those, and for now have no rotation.
    
    CrystalPosition1 = G4ThreeVector(CloverCrystalRadius, CloverCrystalRadius, 9.5*mm);
    CrystalPosition2 = G4ThreeVector(CloverCrystalRadius, -(CloverCrystalRadius), 9.5*mm);
    CrystalPosition3 = G4ThreeVector(-(CloverCrystalRadius), -(CloverCrystalRadius), 9.5*mm);
    CrystalPosition4 = G4ThreeVector(-(CloverCrystalRadius), CloverCrystalRadius, 9.5*mm);
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

    //Define position and rotation for cryo chamber
    
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


