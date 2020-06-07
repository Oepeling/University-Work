package data.vehicles.passsenger;

import data.vehicles.*;

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
}
