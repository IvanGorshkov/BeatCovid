#include "MusicManager.h"
#include "iostream"

MusicManager::MusicManager() {
  backgroundGameMusic.openFromFile("../files/music/1.wav");
//  backgroundMenuMusic.openFromFile();
  hitPlayerBuffer.loadFromFile("../files/music/1.wav");
//  hitEnemyBuffer.loadFromFile();
//  diedEnemyBuffer.loadFromFile();
//  transportBuffer.loadFromFile();
//  walkPlayerBuffer.loadFromFile();
//  jumpPlayerBuffer.loadFromFile();
//  getAntibodiesBuffer.loadFromFile();
//  getVaccineBuffer.loadFromFile();
//  treatPatientBuffer.loadFromFile();
}

void MusicManager::PlayBackgroundGameMusic() {
  backgroundGameMusic.setVolume(10);
  backgroundGameMusic.setLoop(true);
  backgroundGameMusic.play();
}

void MusicManager::PlayBackgroundMenuMusic() {
  backgroundMenuMusic.setVolume(10);
  backgroundMenuMusic.setLoop(true);
  backgroundMenuMusic.play();
}

void MusicManager::PlayHitPlayerSound() {
  hitPlayerSound.setBuffer(hitPlayerBuffer);
  hitPlayerSound.setVolume(10);
  hitPlayerSound.play();
}

void MusicManager::PlayHitEnemySound() {
  hitEnemySound.setBuffer(hitEnemyBuffer);
  hitEnemySound.setVolume(10);
  hitEnemySound.play();
}

void MusicManager::PlayDiedEnemySound() {
  diedEnemySound.setBuffer(diedEnemyBuffer);
  diedEnemySound.setVolume(10);
  diedEnemySound.play();
}

void MusicManager::PlayTransportSound() {
  transportSound.setBuffer(transportBuffer);
  transportSound.setVolume(10);
  transportSound.play();
}

void MusicManager::PlayWalkPlayerSound() {
  walkPlayerSound.setBuffer(walkPlayerBuffer);
  walkPlayerSound.setVolume(10);
  walkPlayerSound.play();
}

void MusicManager::PlayJumpPlayerSound() {
  jumpPlayerSound.setBuffer(jumpPlayerBuffer);
  jumpPlayerSound.setVolume(10);
  jumpPlayerSound.play();
}

void MusicManager::PlayGetAntibodiesSound() {
  getAntibodiesSound.setBuffer(getAntibodiesBuffer);
  getAntibodiesSound.setVolume(10);
  getAntibodiesSound.play();
}

void MusicManager::PlayGetVaccineSound() {
  getVaccineSound.setBuffer(getVaccineBuffer);
  getVaccineSound.setVolume(10);
  getVaccineSound.play();
}

void MusicManager::PlayTreatPatientSound() {
  treatPatientSound.setBuffer(treatPatientBuffer);
  treatPatientSound.setVolume(10);
  treatPatientSound.play();
}