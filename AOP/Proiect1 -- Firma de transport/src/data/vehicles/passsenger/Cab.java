package data.vehicles.passsenger;

public class Cab extends PassengerVehicle {
    private boolean animalFriendly;
    private boolean smokingAllowed;

    public Cab(String licencePlate, Integer capacity) {
        super(licencePlate, capacity);
    }

    public Cab(String licencePlate, Integer capacity, boolean smokingAllowed, boolean animalFriendly) {
        super(licencePlate, capacity);
        this.smokingAllowed = smokingAllowed;
        this.animalFriendly = animalFriendly;
    }

    @Override
    public boolean isAnimalFriendly() {
        return animalFriendly;
    }

    public void setAnimalFriendly(boolean animalFriendly) {
        this.animalFriendly = animalFriendly;
    }

    @Override
    public boolean isSmokingAllowed() {
        return smokingAllowed;
    }

    public void setSmokingAllowed(boolean smokingAllowed) {
        this.smokingAllowed = smokingAllowed;
    }
}
