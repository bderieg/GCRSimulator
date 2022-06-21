#include "ICRP110PhantomDetector.hh"

ICRP110PhantomDetector::ICRP110PhantomDetector(G4String name) : G4VSensitiveDetector(name) {}

ICRP110PhantomDetector::~ICRP110PhantomDetector() {}

// The following function defines what to do on a hit
G4bool ICRP110PhantomDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* R0hist) {
	// G4String outfilename = "particleCounter.csv";

	// Get information on the particle
	// G4Track* track = aStep -> GetTrack();
	// G4String particleName = track -> GetParticleDefinition() -> GetParticleName();
	// G4double initKE = aStep -> GetPreStepPoint() -> GetKineticEnergy();
	// G4ThreeVector position = aStep -> GetPreStepPoint() -> GetPosition();
	// G4double energyDep = aStep -> GetTotalEnergyDeposit();
	// G4String material = aStep -> GetTrack() -> GetMaterial() -> GetName();

	return true;
}