#include "ICRP110PhantomRun.hh"
#include "G4SystemOfUnits.hh"
#include <fstream>

// Upon beginning a run, get the specific detector/scorer we will need
ICRP110PhantomRun::ICRP110PhantomRun() : nEvent(0) {
	G4SDManager* SDM = G4SDManager::GetSDMpointer();
	totalDoseID = SDM -> GetCollectionID("phantomDetector/doseCounter");
	organNameID = SDM -> GetCollectionID("phantomDetector/organName");
	secondaryTypeID = SDM -> GetCollectionID("phantomDetector/secondaryType");
}

ICRP110PhantomRun::~ICRP110PhantomRun() {
}

void ICRP110PhantomRun::RecordEvent(const G4Event* evt) {
	// Tally the number of events and get the hits collection for this event
	nEvent++;
	G4HCofThisEvent* HCE = evt -> GetHCofThisEvent();

	// Get the desired quantities from this event (note that these were stored
	// when the primaries were generated, in ICRP110PhantomPrimaryGeneratorAction.cc)
	G4String eventPrimaryName = evt -> GetPrimaryVertex() -> GetPrimary() -> GetParticleDefinition() -> GetParticleName();
	G4double eventPrimaryKE = evt -> GetPrimaryVertex() -> GetPrimary() -> GetKineticEnergy();

	std::ofstream ofile;
	ofile.open("source_info_later.txt");
	ofile << "primary name: " << eventPrimaryName << "\n";
	ofile.close();

	// Extract information about the dose to get the total dose for this event and store it in newDose
	eventTotalDose = (G4THitsMap<G4double>*)(HCE -> GetHC(totalDoseID));
	std::map<G4int, G4double*>* eventDoseMap = eventTotalDose->GetMap();
	eventOrganNames = (G4THitsMap<G4String>*)(HCE -> GetHC(organNameID));
	std::map<G4int, G4String*>* eventOrganNamesMap = eventOrganNames -> GetMap();
	eventSecondaryNames = (G4THitsMap<G4String>*)(HCE -> GetHC(secondaryTypeID));
	std::map<G4int, G4String*>* eventSecondaryNamesMap = eventSecondaryNames -> GetMap();
	std::map<G4int, G4double*>::iterator itr;
	G4double newDose = 0.0;
	std::map<G4String, G4double> runTissueMap;
	std::map<G4String, G4double> runSecondaryMap;
	std::map<G4String, G4int> runSecondariesByCount;
	for (itr = eventDoseMap->begin(); itr != eventDoseMap->end(); itr++) {
		newDose += *itr->second;	
		runTissueMap[*eventOrganNamesMap->operator[](itr->first)] += *itr->second;
		runSecondaryMap[*eventSecondaryNamesMap->operator[](itr->first)] += *itr->second;
		if (runSecondariesByCount[*eventSecondaryNamesMap->operator[](itr->first)] < 0) {
			runSecondariesByCount[*eventSecondaryNamesMap->operator[](itr->first)] = 0;
		}
		runSecondariesByCount[*eventSecondaryNamesMap->operator[](itr->first)] += 1;
	}

	// Store this information in class variables depending on what the primary particle was
	std::pair<G4String, G4double> keyPair;
	keyPair.first = eventPrimaryName;
	keyPair.second = eventPrimaryKE;
	totalDoses[keyPair] = newDose;

	// Store this information in a different way: according to dose in each organ
	totalDosesByTissue[keyPair] = runTissueMap;

	// Store this information in a different way: according to dose from each type of secondary particle
	totalDosesBySecondary[keyPair] = runSecondaryMap;

	// Store this information in a different way: according to secondary count
	totalSecondariesByCount[keyPair] = runSecondariesByCount;
}

std::map<std::pair<G4String, G4double>, G4double> ICRP110PhantomRun::GetDoseDeposits() {
	return totalDoses;
}

std::map<std::pair<G4String, G4double>, std::map<G4String, G4double>> ICRP110PhantomRun::GetTotalDosesByTissue() {
	return totalDosesByTissue;
}

std::map<std::pair<G4String, G4double>, std::map<G4String, G4double>> ICRP110PhantomRun::GetTotalDosesBySecondary() {
	return totalDosesBySecondary;
}

std::map<std::pair<G4String, G4double>, std::map<G4String, G4int>> ICRP110PhantomRun::GetTotalSecondariesByCount() {
	return totalSecondariesByCount;
}
