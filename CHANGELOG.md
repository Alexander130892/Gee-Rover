# Changelog

Format: [Keep a Changelog](https://keepachangelog.com/en/1.1.0/).

## [Unreleased]

### Added
- Pin map for the 38-pin DevKitC board, avoiding GPIO 16/17 (ADR-0010)
- Bring-up and test plan T01–T17 with pass criteria

### Changed
- Board in BoM and ADR-0001 note: 38-pin AZ-Delivery DevKitC, micro-USB
- BoM: 3× 10 kΩ button pull-ups, extra 100 nF filter capacitor

## [0.0.1] — 2026-10-25

### Added
- Repository structure, README, licenses
- BoM, power architecture, interaction model and sequencer state machine
- ADR-0001 to ADR-0009
- ESP-IDF firmware skeleton
