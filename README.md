# package-tracker

Clean Architecture C++ package tracking example with an in-memory gateway.

## Layers

- **Entities (`src/entities`)**: core enterprise object (`Package`) with no dependency on outer layers.
- **Use cases (`src/use_cases`)**: boundary interfaces, request/response data, and the interactor.
- **Interface adapters (`src/interface_adapters`)**: controller, presenter, view model, and in-memory gateway implementation.
- **Frameworks & drivers (`src/frameworks_drivers`)**: composition root (`main.cpp`) that wires concrete dependencies.

## Dependency Rule

Dependencies point inward only:

- Frameworks & drivers → interface adapters → use cases → entities
- Inner layers never import outer-layer details.

## Round-trip flow

`controller → input boundary → interactor → entity → output boundary → presenter → view model`

1. `TrackPackageController` sends `TrackPackageInputData` to the input boundary.
2. `TrackPackageInteractor` validates tracking input.
3. The interactor loads existing packages through `PackageGateway` or creates a new `Package` entity and saves it.
4. The interactor sends `TrackPackageOutputData` through `TrackPackageOutputBoundary`.
5. `TrackPackagePresenter` maps output to `TrackPackageViewModel`.
6. The driver (`main.cpp`) reads the presenter view model and prints it.

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/package_tracker
```

## Test

```bash
ctest --test-dir build --output-on-failure
```
