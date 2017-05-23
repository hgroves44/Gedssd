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

class DetectionSystemGedssd	
{
public:
    DetectionSystemGedssd();
    ~DetectionSystemGedssd();

    G4int Build() ; //G4SDManager* mySDman);
    //G4int PlaceDetector(G4LogicalVolume* expHallLog, G4int detectorNumber);

private:
    // Assembly volumes
    G4AssemblyVolume* fAssembly;

    //    SensitiveDetector* squareScintSD;
    //    SensitiveDetector* angledScintSD;

    G4double fGeThickDetectorThickness;
    G4double fGeThinDetectorThickness;
    G4double fGeThickDetectorRadius;
    G4double fGeThinDetectorRadius;
    G4double fSpacing;
    G4double fGeThickDetectorCryoOutRad;
    G4double fGeThickDetectorCryoInnRad;
    G4double fGeThickDetectorCryoThickness;

    //##################################################################
    //### methods to construct all of the components of the detector ###
    //##################################################################
    //G4int ConstructWorlds();
    G4int ConstructThinDetector();
    G4int ConstructThickDetectorCryo();
    G4int ConstructCryoEndCap();
    G4int ConstructThickDetector();

    G4PVPlacement* fPhysiGeThinDetector;
    G4PVPlacement* fPhysiGeThickDetector;
    G4PVPlacement* fPhysiGeThickDetectoCryo; 
    G4PVPlacement* fPhysiGeCryoEndCap;
    
    G4LogicalVolume* fLogicThinDetector;
    G4LogicalVolume* fLogicGeThickDetectorCryo;
    G4LogicalVolume* fLogicGeCryoEndCap;
    G4LogicalVolume* fLogiGeThickDetector;

    G4ThreeVector    fGeThinDetectorPos;
    G4ThreeVector    fGeThickDetectorPos;
    G4ThreeVector    fGeCryoEndCapPos1;
    G4ThreeVector    fGeCryoEndCapPos2;
    G4ThreeVector    fGeThickDetectorCryo;
//Logical Volumes
    //
    //G4LogicalVolume* solidWorld;
    //G4LogicalVolume* logicWorld;
    //G4LogicalVolume* physiWorld;
    //G4LogicalVolume* solidGeThickDetector;
    //G4LogicalVolume* logicGeThickDetector;
    //G4LogicalVolume* physiGeThickDetector;
    //G4LogicalVolume* solidGeThinDetector;
    //G4LogicalVolume* logicGeThinDetector;
    //G4LogicalVolume* physiGeThinDetector;
    //G4LogicalVolume* GeThickDetectorMaterial;
    //G4LogicalVolume* GeThinDetectorMaterial;
    //G4LogicalVolume* fWorldLength;
};

#endif

