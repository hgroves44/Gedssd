//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: DetectorConstruction.hh,v 1.1 2010-10-18 15:56:17 maire Exp $
// GEANT4 tag $Name: geant4-09-04-patch-02 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef DetectionSystemGedssd_h
#define DetectionSystemGedssd_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4PVPlacement.hh"
#include "G4AssemblyVolume.hh"
#include "G4SystemOfUnits.hh"

//I am not sure why this class is here. I don't see it in the other .hh files except for the Testcan one. I will leave it for now. 
  
class G4AssemblyVolume;

class DetectionSystemGedssd	
{
public:
    DetectionSystemGedssd();
    ~DetectionSystemGedssd();

    G4int Build() ; //G4SDManager* mySDman);
    G4int PlaceDetector(G4LogicalVolume* expHallLog, G4int detectorNumber);

private:
    // Assembly volumes
    G4AssemblyVolume* fAssemblyGedssd;
    G4AssemblyVolume* fAssemblyClover;

    //Logical Volumes
    G4LogicalVolume* fThickDetectorLog;
    G4LogicalVolume* fThinDetectorLog;
    G4LogicalVolume* fThickDetectorCryoLog;
    G4LogicalVolume* fCryoEndCapLog;
    G4LogicalVolume* fCloverCrystalLog;
    G4LogicalVolume* fCloverCryoLog;

    G4double fConvert;
    G4double fGeThickDetectorThickness;
    G4double fGeThinDetectorThickness;
    G4double fGeThickDetectorRadius;
    G4double fGeThinDetectorRadius;
    G4double fSpacing;
    G4double fGeThickDetectorCryoOutRad;
    G4double fGeThickDetectorCryoInnRad;
    G4double fGeThickDetectorCryoThickness;
    G4double pi;
    G4double fGeCryoEndCapOutRad;
    G4double fGeCryoEndCapThickness;
    G4double CloverCrystalLength;
    G4double CloverCrystalRadius;
    G4double InnerRadius;
    G4double CloverCryox;
    G4double CloverCryoy;
    G4double CloverCryoz;
    G4double fCloverRotate;
    G4double theta;
    G4double theta1;
    G4double theta2;
    G4double theta3;
    G4double theta4;
    G4double theta5;
    G4double theta6;
    G4double theta7;
    G4double theta8;
    G4double theta9;
    G4double phi;
    G4double beta;
    G4double gamma;
    G4double x;
    G4double y;
    G4double z1;
    G4double z9;
    G4double position1;
    G4double position9;
    

    G4int BuildGedssd();

    G4ThreeVector  move;
    G4ThreeVector  direction;
    G4ThreeVector  thinDirection;
    G4ThreeVector  thinPosition;
    G4ThreeVector  thickDirection;
    G4ThreeVector  thickPosition;
    G4ThreeVector  cryoDirection;
    G4ThreeVector  cryoPosition;
    G4ThreeVector  capDirection;
    G4ThreeVector  cap1Position;
    G4ThreeVector  cap2Position;
    G4ThreeVector  CrystalPosition1;
    G4ThreeVector  CrystalPosition2;
    G4ThreeVector  CrystalPosition3;
    G4ThreeVector  CrystalPosition4;
    G4ThreeVector  CloverCryoPosition;
    G4ThreeVector  moveClover1;
    G4ThreeVector  moveClover2;
    G4ThreeVector  moveClover3;
    G4ThreeVector  moveClover4;
    G4ThreeVector  moveClover5;
    G4ThreeVector  moveClover6;
    G4ThreeVector  moveClover7;
    G4ThreeVector  moveClover8;
    G4ThreeVector  moveClover9;
    G4ThreeVector  Ta;
    G4ThreeVector  Tm;

    G4RotationMatrix* Rm;
    G4RotationMatrix* rotate;
    G4RotationMatrix* thinRotation;
    G4RotationMatrix* thickRotation;
    G4RotationMatrix* cryoRotation;
    G4RotationMatrix* capRotation;
    G4RotationMatrix* crystalRotate;
    G4RotationMatrix* CloverCryoRotate;
 
    //G4Transform3D Tr;

};

#endif

