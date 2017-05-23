//This file is a test to replace Sceptar geometries with the gedssd properties to see how it works. I have included the same include files that are in the gedssdnrlDetectorConstruction.cc that were not included originally in the DetectionSystemSceptar.cc file. They are written first.
#include "DetectionSystemGedssd.hh"
//#include "gedssdnrlDetectorConstruction.hh"
//#include "gedssdnrlDetectorMessenger.hh"
//#include "gedssdnrlDetectorSD.hh"
#include "G4UImanager.hh"
#include "G4SDManager.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4RotationMatrix.hh"
#include "G4Material.hh"
//#include "gedssdnrlMaterial.hh"
#include "G4ios.hh"
#include <sstream>

//The below were in the original file, I will comment the ones that were also in the gedssdnrl file with GeFile

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4Tubs.hh"
 //GeFile
#include "G4Box.hh" 
//GeFile
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh" 
//GeFile
#include "G4PVPlacement.hh" 
//GeFile

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4AssemblyVolume.hh"

#include "G4VisAttributes.hh" 
//GeFile
#include "G4Colour.hh" 
//GeFile

#include "DetectionSystemSceptar.hh"

#include "G4SystemOfUnits.hh" 
// new version geant4.10 requires units

DetectionSystemGedssd::DetectionSystemGedssd() :
fPhysiGeThickDetectoCryo(NULL)
    // LogicalVolumes
    //fSquareMylarLog(0),
    //fAngledMylarLog(0),
    //fSquareScintillatorLog(0),
    //fAngledScintillatorLog(0),
    //fDelrinShellLog(0),
    //fDelrinShell2Log(0),
    //fHevimetShellLog(0)
//These above logical volumes don't seem to apply to the Ge detector. I have included the ones in Ge file below.
    //solidWorld(0),
    //logicWorld(0),
    //physiWorld(0),
    //solidGeThickDetector(0),
    //logicGeThickDetector(0),
    //physiGeThickDetector(0),
    //solidGeThinDetector(0),
    //logicGeThinDetector(0),
    //physiGeThinDetector(0),
    //GeThickDetectorMaterial(0),
    //GeThinDetectorMaterial(0),
    //fWorldLength(0)
{

    /////////////////////////////////////////////////////////////////////
    // Detector Properties
    /////////////////////////////////////////////////////////////////////
    //fSeparateHemispheres = 1.0*mm;
    //fConvert = 0.0254*m; //Needed to convert inches to meters

    //fSquareScintillatorLength = 1.194*fConvert;
    //fSquareScintillatorWidth = 0.449*fConvert;
    //fSquareScintillatorThickness = fConvert/16.0;
    //fAngledScintillatorLength  = 1.003*fConvert;
    //fAngledScintillatorLongWidth = 1.045*fConvert;
    //fAngledScintillatorShortWidth = 0.690*fConvert;
    //fAngledScintillatorThickness = fConvert/16.0;
    //fMylarThickness = 0.01*mm;
    //fScintGap = 0.75*mm;
    //fScintAngle1 = 36.0*deg;
   //fScintAngleMove = 18.0*deg;

// These properties are specific to the gedssdn file
    //detectorMessenger = new gedssdnrlDetectorMessenger(this);
  

    fGeThickDetectorThickness = 1.0*cm; // 2.0cm//Hiro's detector
    fGeThinDetectorThickness = 1.5*mm;
    fGeThickDetectorRadius = 4.5*cm; // 3.0 * cm; //3.0*cm;Hiro's detector
    fGeThinDetectorRadius = 4.5 * cm;
    fSpacing = 5*mm;
    pi = 3.14159265358979323846; 
}
    //fUseGeThinDetector = true;
    //fUseGeThickDetector= true;
    //fUseGeThickDetectorCryo= true;
    //fUseGeThickDetectorCryoEndCap= true;

    //fUseSega = false;
    //fUseClover = false;
//--------- Sizes of the principal geometrical components (solids)  ---------
  //fWorldLength = fGeThickDetectorThickness + 50*cm;
  //fWorldRadius = fGeThickDetectorRadius + 50.*cm;

//The below function was written originally for the Sceptar but same idea as what I have below for the Ge
DetectionSystemGedssd::~DetectionSystemGedssd() {
  //  delete detectorMessenger;
}
//There is no build function in the Gedssd file so I am going to attempt to adapt this to work with the Ge
G4int DetectionSystemGedssd::Build() {
    // Build assembly volume
    G4AssemblyVolume* myAssemblyGedssd = new G4AssemblyVolume();
    this->assemblyGedssd = myAssemblyGedssd;

    ConstructThinDetector();
    ConstructThickDetector();
    ConstructThickDetectorCryo();
    ConstructCryoEndCap();

    return 1;
}
//Going to try building it without the placement function and just have that in construct functions
//G4int DetectionSystemSceptar::PlaceDetector(G4LogicalVolume* expHallLog, G4int detectorNumber) {

    //G4RotationMatrix* rotateNull = new G4RotationMatrix;
    //G4ThreeVector moveNull(0.0,0.0,0.0);

//*****************************************************************
// Below are all of the ::Construct functions necessary to build
// the assembly of Gedssd 
//*****************************************************************

//*****************************************************************
//Construction of the worlds
//*****************************************************************
////G4int DetectionSystemGedssd::ConstructWorlds() {
//
//    solidWorld = newG4Tubs("world",0.,fWorldRadius,fWorldLength/2.,0.,twopi);
//    G4Material* DefaultMaterial = G4Material::GetMaterial("vacuum");
//    logicWorld = new G4LogicalVolume( solidWorld, DefaultMaterial, "World", 0, 0, 0);
//    physiWorld = new G4VPlacement(0,  		   // no rotation
//                                  G4ThreeVector(), //at origin
//                                  logicWorld,	   //it's logical volume
//				  "World",	   // it's name
//				  0,		   // its mother volume
//				  false,           // no boolean operations
//				  0);              // no field specific to volume
//}

//*****************************************************************
// Construction of Thin Detector
//*****************************************************************
//This structure is very similar to the Testcan structure that Joey has up on github
//He has two commands that I don't have and they are the G4ThreeVector and G4RotationMatrix
//In the original file, it had each part of the detector built separately. In Joey's file, he picks the materials, builds each, defines visual attributes, then movements.Something I am not using that Joey uses a lot is the this-> command. But it seems like otherwise, everything I have is exactly what he has. Different order, but all the same commands. 
G4int DetectionSystemGedssd::ConstructThinDetector() {
    G4Material*GeThinDetectorMaterial = G4Material::GetMaterial("Ge");
    if( !GeThinDetectorMaterial ) {
        G4cout << " ----> Material " << "Ge" << " not found, cannot build the detector shell! " << G4endl;
        return 0;
    }
    //Add position element
    fGeThinDetectorPos = G4ThreeVector(0,0,-(fGeThickDetectorThickness/2.)-(fGeThinDetectorThickness/2.)-fSpacing);

    //Putting in placement command to replace placement function 
    //For below, I think that we can try getting rid of the G4PVPlacement function. Joey doesn't use it, so we will comment out and see how that goes.
   // if(UseGeThinDetector){
//    fPhysiGeThinDetector = new G4PVPlacement(0, fGeThinDetectorPos,fLogicThinDetector,"GeThinDetector",fLogicGeThickDetectorCryo,false,0);
 //   }

    //The visual attributes is the same as it's programmed in Testcan 
    G4VisAttributes* ThinDetectorVisAtt = new G4VisAttributes(G4Colour(0.1,0.1,0.1));
    ThinDetectorVisAtt->SetVisibility(true);
  
    //The below line replaced the SubtractionSolid since it is necessary for the logical volume

    G4Tubs* solidGeThinDetector = new G4Tubs("GeThinDetector",0.,fGeThinDetectorRadius,fGeThinDetectorThickness/2.,0.,2*pi);
    fLogicThinDetector = new G4LogicalVolume(solidGeThinDetector, GeThinDetectorMaterial, "GeThinDetector", 0, 0, 0);
    fLogicThinDetector->SetVisAttributes(ThinDetectorVisAtt);

    //need to find this and replace with other file information. Think I may leave in the rotate Null since not really doing anyting

    G4RotationMatrix* rotateNull = new G4RotationMatrix;


    this->assemblyGedssd->AddPlacedVolume(fLogicThinDetector, fGeThinDetectorPos, rotateNull);

    return 1;
} //end ::ConstructThinDetector

//*******************************************************************
// Construction of Thick Detectory Cryo Chamber
//*******************************************************************

G4int DetectionSystemGedssd::ConstructThickDetectorCryo() {
    G4Material* GeThickDetectorCryoMaterial = G4Material::GetMaterial("Al");
    if( !GeThickDetectorCryoMaterial ) {
	G4cout << " ----> Material " << "Al" << " not found, cannot build the Thick Cryo!" << G4endl;
	return 0;
    }
    
    fGeThickDetectorCryoPos = G4ThreeVector(0,0,0);
    fGeThickDetectorCryoOutRad = 9.6393*cm; //from Ethan
    fGeThickDetectorCryoInnRad = 6.6*cm;
    fGeThickDetectorCryoThickness = 8.89*cm; //measured with a tape measurer

    //if(fUseGeThickDetectorCryo) {
    //fPhysiGeThickDetectoCryo = new G4PVPlacement(0,fGeThickDetectorCryoPos,fLogicGeThickDetectorCryo,"GeThickDetectorCryo",logicWorld,false,0,true);
    //}

    G4VisAttributes* ThickDetectorCryoVisAtt = new G4VisAttributes(G4Colour::Blue());
    ThickDetectorCryoVisAtt->SetVisibility(true); 

    G4Tubs* solidGeThickDetectorCryo = new G4Tubs("GeThickDetectorCryo",fGeThickDetectorCryoInnRad,fGeThickDetectorCryoOutRad,fGeThickDetectorCryoThickness/2.,0.,2*pi);
    fLogicGeThickDetectorCryo = new G4LogicalVolume(solidGeThickDetectorCryo,GeThickDetectorCryoMaterial,"GeThickDetectorCryo",0,0,0);
    fLogicGeThickDetectorCryo->SetVisAttributes(ThickDetectorCryoVisAtt);

    this->assemblyGedssd->AddPlacedVolume(fLogicGeThickDetectorCryo, fGeThickDetectorCryoPos, rotateNull);

    return 1;
} //end ::ConstructThickDetectorCryo

//*****************************************************************
// Construction of the Cryo End Caps
//*****************************************************************

G4int DetectionSystemGedssd::ConstructCryoEndCap() {
    G4Material* GeCryoEndCapMaterial = G4Material::GetMaterial("Al");
    if( !GeCryoEndCapMaterial ) {
	G4cout <<" ----> Material " << "Al" << "not found, cannot build the Cryo End Cap!" << G4endl;
	return 0;
    }

    fGeCryoEndCapOutRad = fGeThickDetectorCryoInnRad;
    fGeCryoEndCapThickness = 1.143*mm; //use 0.1 cm for radioxenon
    //There are two end caps, so two positions
    fGeCryoEndCapPos1 = G4ThreeVector(0,0,fGeThickDetectorCryoThickness/2. - fGeCryoEndCapThickness/2.);
    fGeCryoEndCapPos2 = G4ThreeVector(0,0,-fGeThickDetectorCryoThickness/2. + fGeCryoEndCapThickness/2.);

    //if(fUseGeThickDetectorCryoEndCap){
    //fPhysiGeCryoEndCap = new G4PVPlacement(0,fGeCryoEndCapPos1,fLogicGeCryoEndCap,"GeCryoEndCap",logicWorld,false,0,true);
    //fPhsyiGeCryoEndCap = new G4PVPlacement(0,fGeCryoEndCapPos2,fLogicGeCryoEndCap,"GeCryoEndCap",logicWorld,false,1,true);
    //}

    G4VisAttributes* CryoEndCapVisAtt = new G4VisAttributes(G4Colour::Green());
    CryoEndCapVisAtt->SetVisibility(true);

    G4Tubs* solidGeCryoEndCap = new G4Tubs("GeCryoEndCap",0.,fGeCryoEndCapOutRad,fGeCryoEndCapThickness/2.,0.,2*pi);
    fLogicGeCryoEndCap = new G4LogicalVolume(solidGeCryoEndCap,GeCryoEndCapMaterial,"GeCryoEndCap",0,0,0);
    fLogicGeCryoEndCap->SetVisAttributes(CryoEndCapVisAtt);

    this->assemblyGedssd->AddPlacedVolume(fLogicGeCryoEndCap, fGeCryoEndCapPos1, rotateNull);
    this->assemblyGedssd->AddPlacedVolume(fLogicGeCryoEndCap, fGeCryoEndCapPos2, rotateNull);

    return 1;
}//end ::ConstructCryoEndCap

//*****************************************************************
// Construction of the Thick Detector
//*****************************************************************

G4int DetectionSystemGedssd::ConstructThickDetector() {
   G4Material* GeThickDetectorMaterial = G4Material::GetMaterial("Ge");
   if( !GeThickDetectorMaterial ) {
	G4cout << "-----> Material Ge not found, cannot build the Thick Detector!" <<G4endl;
	return 0;
   }

   fGeThickDetectorPos = G4ThreeVector(0,0,0);

   //if(fUseGeThickDetector){
    //fPhysiGeThickDetector = new G4PVPlacement(0,fGeThickDetectorPos,fLogicGeThickDetector,"GeThickDetector",logicWorld,false,0,true);
    //}

   G4VisAttributes* ThickDetectorVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,.0));
   ThickDetectorVisAtt->SetVisibility(true);

   G4Tubs* solidGeThickDetector = new G4Tubs("GeThickDetector",0,fGeThickDetectorRadius,fGeThickDetectorThickness/2.,0.,2*pi);
   fLogicGeThickDetector = new G4LogicalVolume(solidGeThickDetector,GeThickDetectorMaterial,"GeThickDetector",0,0,0);

   fLogicGeThickDetector->SetVisAttributes(ThickDetectorVisAtt);

   this->assemblyGedssd->AddPlacedVolume(fLogicGeThickDetector, fGeThickDetectorPos, rotateNull);

   return 1;
} //end ::ConstructThickDetector

//*******************************************************************
//Construct2ndDelrinShell builds a spherical shell of Delrin around
//the first sphere of Delrin, with two holes in it for the beam line.
//This is to simulate the Delrin in front of the germanium detectors
//*******************************************************************

//G4int DetectionSystemSceptar::Construct2ndDelrinShell() {
  //  G4Material* materialDelrin = G4Material::GetMaterial("Delrin");
  //  if( !materialDelrin ) {
  //      G4cout << " ----> Material " << "Delrin" << " not found, cannot build the detector shell! " << G4endl;
  //      return 0;
  //  }

  //  G4VisAttributes* Delrin2VisAtt = new G4VisAttributes(G4Colour(1,1,1));
  //  Delrin2VisAtt->SetVisibility(true);

  //  G4SubtractionSolid* shell2 = DelrinShell2();

  //  fDelrinShell2Log = new G4LogicalVolume(shell2, materialDelrin, "DelrinShell2Log", 0, 0, 0);
  //  fDelrinShell2Log->SetVisAttributes(Delrin2VisAtt);

  //  G4RotationMatrix* rotateNull = new G4RotationMatrix;
  //  G4ThreeVector moveNull(0.0,0.0,0.0);

  //  fAssembly->AddPlacedVolume(fDelrinShell2Log, moveNull, rotateNull);

 //   return 1;

//} //end ::Construct2ndDelrinShell


///////////////////////////////////////////////////////////////////////
// Methods used to build shapes
// I left this as an example of how they had done this previously
///////////////////////////////////////////////////////////////////////

//G4SubtractionSolid* DetectionSystemSceptar::DelrinShell2() {
//    G4Sphere* sphere = new G4Sphere("sphere", fDelrin2InnerRadius, fDelrin2OuterRadius, 0, 2.0*M_PI, 0, M_PI);

//    G4Tubs* chopTub = new G4Tubs("chopTub", 0, fDelrinHoleRadius, fDelrin2OuterRadius +1.0, 0, 2.0*M_PI);

//    G4RotationMatrix* rotateChopTub = new G4RotationMatrix;
//    rotateChopTub->rotateX(-M_PI/2.0);

//    G4ThreeVector moveNull(0.0,0.0,0.0);

//    G4SubtractionSolid* delrinShell2 = new G4SubtractionSolid("DelrinShell2", sphere, chopTub, rotateChopTub, moveNull);

//    return delrinShell2;
//} //end ::DelrinShell2



