package services;

import data.*;
import data.routes.Route;
import data.settlements.*;
import data.roads.*;
import data.vehicles.*;
import data.vehicles.passsenger.*;
import data.vehicles.cargo.*;

import java.util.ArrayList;
import java.util.List;

import static java.lang.Math.round;

public class TransportCompanyService extends TransportCompany {
    public void addSettlement(String name, String type) {
        addSettlement(name, type, 0);
    }

    public void addSettlement(String name, String type, int population) {
        BaseSettlement toAdd;
        switch (type) {
            case "Hamlet":
                toAdd = new Hamlet(name, population);
                break;
            case "Village":
                toAdd = new Village(name, population);
                break;
            case "Town":
                toAdd = new Town(name, population);
                break;
            case "City":
                toAdd = new City(name, population);
                break;
            default:
                return;
        }
        super.addSettlement(toAdd);
    }

    public void addRoad(String name, String from, String to, String type) {
        addRoad(name, from, to, type, 0);
    }

    public void addRoad(String from, String to, String type) {
        addRoad("", from, to, type, 0);
    }

    public void addRoad(String from, String to, String type, int length) { addRoad(from, to, type, length, true); }

    public void addRoad(String from, String to, String type, int length, boolean two_way) { addRoad("", from, to, type, length, two_way); }

    public void addRoad(String name, String from, String to, String type, int length) { addRoad(name, from, to, type, length, true); }

    public void addRoad(String name, String from, String to, String type, int length, boolean two_way) {
        BaseSettlement fromS = super.findSettlement(from);
        BaseSettlement toS = super.findSettlement(to);
        if (fromS == null || toS == null) {
            // Naspa
            return;
        }

        BaseRoad toAdd;
        switch (type) {
            case "RuralRoad":
                toAdd = new RuralRoad(name, fromS, toS, length);
                break;
            case "DistrictRoad":
                toAdd = new DistrictRoad(name, fromS, toS, length);
                break;
            case "StateHighway":
                toAdd = new StateHighway(name, fromS, toS, length);
                break;
            case "NationalHighway":
                toAdd = new NationalHighway(name, fromS, toS, length);
                break;
            default:
                return;
        }

        super.addRoad(toAdd, two_way);
    }

    public void addVehicle(String licencePlate,
                           String type,
                       Integer capacity) {
        addVehicle(licencePlate, type, capacity, false, false);
    }

    public void addVehicle(String licencePlate,
                           String type,
                           Integer capacity,
                           boolean smokingAllowed) {
        addVehicle(licencePlate, type, capacity, smokingAllowed, false);
    }

    public void addVehicle(String licencePlate,
                           String type,
                           Integer capacity,
                           boolean smokingAllowed,
                           boolean animalFriendly) {
        BaseVehicle toAdd;
        switch (type) {
            case "Cab":
                toAdd = new Cab(licencePlate, capacity, smokingAllowed, animalFriendly);
                break;
            case "MiniBus":
                toAdd = new MiniBus(licencePlate, capacity);
                break;
            case "Bus":
                toAdd = new Bus(licencePlate, capacity);
                break;
            default:
                addVehicle(licencePlate, type, capacity);
                return;
        }

        super.addVehicle(toAdd);
    }

    public void addVehicle(String licencePlate, String type, Float capacity) {
        BaseVehicle toAdd;
        switch (type) {
            case "Bicycle":
                toAdd = new Bicycle(licencePlate, capacity);
                break;
            case "Car":
                toAdd = new Car(licencePlate, capacity);
                break;
            case "Truck":
                toAdd = new Truck(licencePlate, capacity);
                break;
            default:
                return;
        }

        super.addVehicle(toAdd);
    }

    public void addVehicle(String licencePlate,
                           String type,
                           Float capacity,
                           boolean smokingAllowed,
                           boolean animalFriendly) {
        BaseVehicle toAdd;
        if (type.equals("Bicycle")) {
            toAdd = new Bicycle(licencePlate, capacity);
        } else if (type.equals("Car")) {
            toAdd = new Car(licencePlate, capacity);
        } else if (type.equals("Truck")) {
            toAdd = new Truck(licencePlate, capacity);
        } else {
            addVehicle(licencePlate, type, round(capacity), smokingAllowed, animalFriendly);
            return;
        }

        super.addVehicle(toAdd);
    }

    public void addTransportRoute(List<String> stops) {
        List<BaseSettlement> realStops = new ArrayList<>();
        for (String stop : stops) {
            BaseSettlement currStop = super.findSettlement(stop);
            if (currStop == null) {
                // Naspa
                return;
            }
            realStops.add(currStop);
        }
            
        super.addRoute(super.findRoute(realStops));
    }

    public void putVehicleOnRoute(String licencePlate, int routeId) {
        super.putVehicleOnRoute(super.findVehicle(licencePlate), super.findRouteById(routeId));
    }

    public List<BaseSettlement> getSettlements() {
        return super.getSettlements();
    }

    public List<BaseRoad> getRoads() {
        return super.getRoads();
    }

    public List<BaseVehicle> getVehicles() {
        return super.getVehicles();
    }

    public List<Route> getRoutes() {
        return super.getRoutes();
    }

    public List<BaseVehicle> getVehiclesOnRoute(Route route) {
        return super.getVehiclesOnRoute(route);
    }
}
