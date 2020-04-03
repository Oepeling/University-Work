import java.util.ArrayList;
import java.util.List;
import java.util.Map;

class Route {
    protected List<BaseSettlement> settlements;
    protected List<BaseRoad> roads;
    protected boolean truckOnly;
}

public class TransportCompany {
    private Map<BaseSettlement, List<BaseRoad>> graph;
    private List<Route> routes;
    private List<CargoVehicle> cargoVehicles;
    private List<PassengerVehicle> passengerVehicles;
    private Map<Route, List<BaseVehicle>> activeRoutes;

    public void addSettlement(BaseSettlement settlement) {
        graph.put(settlement, new ArrayList<>());
    }

    public void addRoad(BaseRoad road) {
        graph.get(road.getFrom()).add(road);
    }

    public void addRoute(Route route) {
        if (routes.contains(route)) {
            // Naspa
        } else {
            routes.add(route);
            activeRoutes.put(route, new ArrayList<>());
        }
    }

    public void addVehicle(CargoVehicle vehicle) {
        if (cargoVehicles.contains(vehicle)) {
            // Naspa
        } else {
            cargoVehicles.add(vehicle);
        }
    }

    public void addVehicle(PassengerVehicle vehicle) {
        if (passengerVehicles.contains(vehicle)) {
            // Naspa
        } else {
            passengerVehicles.add(vehicle);
        }
    }

    public void addVehicle(BaseVehicle vehicle) {
        if (vehicle instanceof CargoVehicle) {
            addVehicle((CargoVehicle) vehicle);
        } else if (vehicle instanceof PassengerVehicle) {
            addVehicle((PassengerVehicle) vehicle);
        } else {
            // Naspa
        }
    }

    public void putVehicleOnRoute(Route route, BaseVehicle vehicle) {
        addRoute(route);
        addVehicle(vehicle);

        if (route.truckOnly && vehicle.getClass() != Truck.class) {
            // Naspa
        } else {
            if (activeRoutes.get(route).contains(vehicle)) {
                // Naspa
            } else {
                activeRoutes.get(route).add(vehicle);
            }
        }
    }
}
