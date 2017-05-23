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

    //Logical Volumes
    G4LogicalVolume* fThickDetectorLog;
    G4LogicalVolume* fThinDetectorLog;
    G4LogicalVolume* fThickDetectorCryoLog;
    G4LogicalVolume* fCryoEndCapLog;

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

    //G4String fThinMaterial;
    //G4String fThickMaterial;
    //G4String fCryoMaterial;
    //G4String fEndCapMaterial;

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

    G4RotationMatrix* rotate;
    G4RotationMatrix* thinRotation;
    G4RotationMatrix* thickRotation;
    G4RotationMatrix* cryoRotation;
    G4RotationMatrix* capRotation;
 
};

#endif

