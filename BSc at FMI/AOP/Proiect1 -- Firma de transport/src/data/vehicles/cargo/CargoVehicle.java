package data.vehicles.cargo;

import data.vehicles.*;

public abstract class CargoVehicle extends BaseVehicle {
    private float capacityKg;

    protected CargoVehicle(String licencePlate, Float capacity) {
        super(licencePlate);
        capacityKg = capacity;
    }

    @Override
    public float getCapacity() {
        return capacityKg;
    }

    public void setCapacity(float capacityKg) {
        this.capacityKg = capacityKg;
    }

    @Override
    public String toString() {
        return String.format("Licence plate: %s; Cargo Type: %s; Capacity: %f kg",
                getLicencePlate(),
                getClass().getSimpleName(),
                getCapacity());
    }
}
