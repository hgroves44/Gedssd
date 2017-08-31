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
/// \file analysis/shared/include/SteppingAction.hh
/// \brief Definition of the SteppingAction class
//
//
// $Id: SteppingAction.hh 68015 2013-03-13 13:27:27Z gcosmo $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "globals.hh"
#include "G4UserSteppingAction.hh"

class DetectorConstruction;
class EventAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SteppingAction : public G4UserSteppingAction
{
public:
    SteppingAction(DetectorConstruction*, EventAction*);
    virtual ~SteppingAction();

    virtual void UserSteppingAction(const G4Step*);
    
private:
    DetectorConstruction* fDetector;
    EventAction*          fEventAction;

    // Griffin
    void SetDetAndCryNumberForGriffinComponent( G4String );
    void SetDetAndCryNumberForDeadLayerSpecificGriffinCrystal(G4String);
    void SetDetNumberForGenericDetector( G4String );
    void SetDetNumberForAncillaryBGODetector( G4String );

    G4int FindTrueGriffinDetector(G4int);

    G4int fStepNumber;
    G4int fDet;
    G4int fCry;
    G4int fTrueGriffinDetectorMap[16];
    G4bool fGriffinDetectorMapSet;

    G4int fNumberOfAssemblyVols;

    G4String G4intToG4String(G4int value);
    G4String GetCrystalColour(G4int value);

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
