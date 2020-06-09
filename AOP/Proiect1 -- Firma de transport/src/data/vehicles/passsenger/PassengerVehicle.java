package data.vehicles.passsenger;

import data.vehicles.*;

import java.lang.Math;

public abstract class PassengerVehicle extends BaseVehicle {
    private int capacity;

    protected PassengerVehicle(String licencePlate, Integer capacity) {
        super(licencePlate);
        this.capacity = capacity;
    }

    @Override
    public float getCapacity() {
        return capacity;
    }

    public void setCapacity(int capacity) {
        this.capacity = capacity;
    }

    @Override
    public String toString() {
        return String.format("Licence plate: %s; Passenger Type: %s; Capacity: %d people",
                getLicencePlate(),
                getClass().getSimpleName(),
                Math.round(getCapacity()));
    }
}
