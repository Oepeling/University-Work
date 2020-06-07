package data.vehicles;

public abstract class BaseVehicle {
    private static int index = 0;
    private int idCode;
    private String licencePlate;

    BaseVehicle() {
        idCode = index;
        licencePlate = "";
        index++;
    }

    protected BaseVehicle(String licencePlate) {
        this.licencePlate = licencePlate;
        idCode = index;
        index++;
    }

    @Override
    public void finalize() {
        index--;
    }

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

    public float getCapacity() { return 0; }

    public boolean isSmokingAllowed() { return false; }

    public boolean isAnimalFriendly() { return false; }
}
