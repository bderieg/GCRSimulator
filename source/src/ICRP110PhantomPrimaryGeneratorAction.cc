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
// Code developed by:
// S.Guatelli, M. Large and A. Malaroda, University of Wollongong
//
// 
//
#include "ICRP110PhantomPrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include <fstream>

ICRP110PhantomPrimaryGeneratorAction::ICRP110PhantomPrimaryGeneratorAction()
{
  fParticleGun = new G4GeneralParticleSource();
}

ICRP110PhantomPrimaryGeneratorAction::~ICRP110PhantomPrimaryGeneratorAction()
{
  delete fParticleGun;
}

void ICRP110PhantomPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fParticleGun -> GeneratePrimaryVertex(anEvent);

//  G4cout << "Particle source // particle type: " << fParticleGun->GetCurrentSource()->GetParticleDefinition()->GetParticleName() << ", source radius: " << fParticleGun->GetCurrentSource()->GetPosDist()->GetRadius() << G4endl;

  // Add information about the generated primary particle to the event
 // G4PrimaryVertex* primVert = new G4PrimaryVertex();
 // G4PrimaryParticle* primPart = new G4PrimaryParticle();
 // primPart -> SetKineticEnergy(fParticleGun->GetParticleEnergy());
 // primPart -> SetParticleDefinition(fParticleGun -> GetParticleDefinition());
 // primVert -> SetPrimary(primPart);
 // anEvent -> AddPrimaryVertex(primVert);
 
// std::ofstream ofile;
// ofile.open("source_info.txt");
// ofile << "particle type: " << fParticleGun->GetCurrentSource()->GetParticleDefinition()->GetParticleName() << "\n";
// ofile << "source radius: " << fParticleGun->GetCurrentSource()->GetPosDist()->GetRadius() << "\n";
// ofile << "primary vertex: " << "\n";
// ofile << "\tenergy: " << anEvent->GetPrimaryVertex()->GetPrimary()->GetKineticEnergy() << "\n";
// ofile << "\tname: " << anEvent->GetPrimaryVertex()->GetPrimary()->GetParticleDefinition()->GetParticleName() << "\n";
// ofile.close();
}

