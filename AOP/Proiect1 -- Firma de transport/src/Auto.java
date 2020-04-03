abstract class BaseVehicle {
    private int idCode;
    private String licencePlate;

    public int getIdCode() {
        return idCode;
    }

    public void setIdCode(int idCode) {
        this.idCode = idCode;
    }

    public String getLicencePlate() {
        return licencePlate;
    }

    public void setLicencePlate(String licencePlate) {
        this.licencePlate = licencePlate;
    }
}

abstract class CargoVehicle extends BaseVehicle {
    private float capacityKg;

    public float getCapacityKg() {
        return capacityKg;
    }

    public void setCapacityKg(float capacityKg) {
        this.capacityKg = capacityKg;
    }
}

abstract class PassengerVehicle extends BaseVehicle {
    private int capacity;

    public int getCapacity() {
        return capacity;
    }

    public void setCapacity(int capacity) {
        this.capacity = capacity;
    }
}

class Bicycle extends CargoVehicle {
}

class Car extends CargoVehicle {
}

class Truck extends CargoVehicle {
}

class Cab extends PassengerVehicle {
    private boolean animalFriendly;
    private boolean smokingAllowed;

    public boolean isAnimalFriendly() {
        return animalFriendly;
    }

    public void setAnimalFriendly(boolean animalFriendly) {
        this.animalFriendly = animalFriendly;
    }

    public boolean isSmokingAllowed() {
        return smokingAllowed;
    }

    public void setSmokingAllowed(boolean smokingAllowed) {
        this.smokingAllowed = smokingAllowed;
    }
}

class MiniBus extends PassengerVehicle {
}

class Bus extends PassengerVehicle {
}
