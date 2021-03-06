package services;

import data.*;
import data.routes.Route;
import data.settlements.*;
import data.roads.*;
import data.vehicles.*;
import data.vehicles.passsenger.*;
import data.vehicles.cargo.*;

import javax.swing.*;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import static java.lang.Math.round;

public class TransportCompanyService extends TransportCompany {
    private static TransportCompanyService instance = null;
    private DatabaseHandler dbh;
    private Audit audit = Audit.getInstance();

    public TransportCompanyService() {
        try {
            dbh = new DatabaseHandler();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static TransportCompanyService getInstance() {
        if (instance == null) {
            instance = new TransportCompanyService();
        }
        return instance;
    }

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
        audit.write("Add,settlement," + toAdd.toString());
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
        audit.write("Add,road," + toAdd.toString());
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
        if (super.findVehicle(licencePlate) != null) {
            return;
        }
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
                addVehicle(licencePlate, type, (float)capacity);
                return;
        }

        super.addVehicle(toAdd);
        audit.write("Add,vehicle," + toAdd.toString());
    }

    public void addVehicle(String licencePlate, String type, Float capacity) {
        if (super.findVehicle(licencePlate) != null) {
            return;
        }
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
        audit.write("Add,vehicle," + toAdd.toString());
    }

    public void addVehicle(String licencePlate,
                           String type,
                           Float capacity,
                           boolean smokingAllowed,
                           boolean animalFriendly) {
        if (super.findVehicle(licencePlate) != null) {
            return;
        }
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
                addVehicle(licencePlate, type, round(capacity), smokingAllowed, animalFriendly);
                return;
        }

        super.addVehicle(toAdd);
        audit.write("Add,vehicle," + toAdd.toString());
    }

    public int addTransportRoute(List<String> stops) {
        List<BaseSettlement> realStops = new ArrayList<>();
        for (String stop : stops) {
            BaseSettlement currStop = super.findSettlement(stop);
            if (currStop == null) {
                // Naspa
                return -1;
            }
            realStops.add(currStop);
        }

        String s = "Add,route,";
        for (String stop : stops) {
            s = s + stop + ';';
        }
        s = s.substring(0, s.length() - 1);
        audit.write(s);
        return super.addRoute(super.findRoute(realStops));
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

    public Map<Route, List<BaseVehicle>> getActiveRoutes() { return super.getActiveRoutes(); }

    public void guiStarter() {
        MyThread myThread = new MyThread();
        myThread.start();
    }

    public void guiHandler(JFrame frame, int action) {
        frame.dispose();
        StringBuilder s = new StringBuilder();

        if (action == 0) {
            // log("Back to menu");
            GUI gui = new GUI();
            return;
        } else if (action == 6) {
            // log("Exit");
            return;
        } else if (action == 1) {
            // log("Show settlements");
            for (BaseSettlement settlement : this.getSettlements()) {
                s.append(settlement).append("&");
            }
        } else if (action == 2) {
            // log("Show roads");
            for (BaseRoad road : this.getRoads()) {
                s.append(road).append("&");
            }
        } else if (action == 3) {
            // log("Show routes");
            for (Route route : this.getRoutes()) {
                s.append(route).append("&");
            }
        } else if (action == 4) {
            // log("Show vehicles");
            for (BaseVehicle vehicle : this.getVehicles()) {
                s.append(vehicle).append("&");
            }
        } else if (action == 5) {
            // log("Show vehicles on route");
            for (Map.Entry<Route, List<BaseVehicle>> entry : this.getActiveRoutes().entrySet()) {
                if (!entry.getValue().isEmpty()) {
                    s.append("Route: ").append(entry.getKey().getId()).append("; Vehicles: ");
                    for (BaseVehicle vehicle : entry.getValue()) {
                        s.append(vehicle.getLicencePlate()).append(", ");
                    }
                    s = new StringBuilder(s.substring(0, s.length() - 2) + "&");
                }
            }
        }
        GUI2 gui2 = new GUI2(s.toString().split("&"));
    }

    private void recoverFromBackup() {
        try {
            if (dbh.existsTable("settlements")) {
                dbh.readSettlements(instance);
            }
            if (dbh.existsTable("roads")) {
                dbh.readRoads(instance);
            }
            if (dbh.existsTable("vehicles")) {
                dbh.readVehicles(instance);
            }
            if (dbh.existsTable("routes")) {
                dbh.readRoutes(instance);
            }
            if (dbh.existsTable("routes_vehicles")) {
                dbh.readRouteVehicle(instance);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private void makeBackup() {
        try {
            dbh.dropTable("settlements");
            dbh.createSettlementsTable(instance);
            dbh.dropTable("roads");
            dbh.createRoadsTable(instance);
            dbh.dropTable("vehicles");
            dbh.createVehiclesTable(instance);
            dbh.dropTable("routes");
            dbh.createRoutesTable(instance);
            dbh.dropTable("routes_vehicles");
            dbh.createRouteVehicleTable(instance);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void master() {
        recoverFromBackup();
        guiStarter();
        makeBackup();
    }
}
