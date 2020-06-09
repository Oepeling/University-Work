package data;

import data.settlements.*;
import data.roads.*;
import data.vehicles.*;
import data.vehicles.passsenger.*;
import data.vehicles.cargo.*;
import data.routes.*;

import java.util.*;

class TransportNetwork {
    private List<BaseSettlement> nodes;
    private Map<BaseSettlement, List<BaseRoad>> edges;

    protected TransportNetwork() {
        nodes = new ArrayList<>();
        edges = new HashMap<>();
    }

    protected void addSettlement(BaseSettlement settlement) {
        if (!nodes.contains(settlement)) {
            nodes.add(settlement);
            edges.put(settlement, new ArrayList<>());
        }
    }

    protected void addRoad(BaseRoad road) {
        edges.get(road.getFrom()).add(road);
    }

    protected BaseSettlement findSettlement(String name) {
        for (BaseSettlement i : nodes) {
            if (i.getName().equals(name)) {
                return i;
            }
        }
        return null;
    }

    private static class Path {
        List<BaseSettlement> path_nodes;
        List<BaseRoad> path_edges;

        protected Path() {
            path_nodes = new ArrayList<>();
            path_edges = new ArrayList<>();
        }

        protected void addNode(BaseSettlement node) {
            path_nodes.add(node);
        }
        protected void addEdge(BaseRoad edge) {
            path_edges.add(edge);
        }

        protected void reverse() {
            Collections.reverse(path_nodes);
            Collections.reverse(path_edges);
        }
    }

    public Path findWay(BaseSettlement source, BaseSettlement dest) {
        Map<BaseSettlement, Integer> dist = new HashMap<>();
        Map<BaseSettlement, BaseRoad> parent = new HashMap<>();

        Comparator<BaseSettlement> comparator = (o1, o2) -> dist.get(o1) - dist.get(o2);
        PriorityQueue<BaseSettlement> heap = new PriorityQueue<>(comparator);

        dist.put(source, 0);
        heap.add(source);
        while (!heap.isEmpty()) {
            BaseSettlement node = heap.poll();
            if (node == dest) {
                break;
            }

            List<BaseRoad> currEdges = edges.get(node);

            for (BaseRoad road : currEdges) {
                BaseSettlement next = road.getTo();
                Integer newDist = dist.get(node) + road.getLength();
                if (!dist.containsKey(next) || dist.get(next) > newDist) {
                    heap.remove(next);
                    dist.put(next, newDist);
                    parent.put(next, road);
                    heap.add(next);
                }
            }
        }

        Path answer = new Path();

        if (!dist.containsKey(dest)) {
            // Naspa
            return null;
        } else {
            BaseSettlement node = dest;
            while(node != source) {
                answer.addNode(node);
                answer.addEdge(parent.get(node));
                node = parent.get(node).getFrom();
            }
            answer.reverse();
            return answer;
        }
    }

    public Route findRoute(List<BaseSettlement> stops) {
        List<BaseSettlement> settlements = new ArrayList<>();
        List<BaseRoad> roads = new ArrayList<>();

        if (stops.isEmpty()) {
            return null;
        } else {
            settlements.add(stops.get(0));
        }

        for (int i = 1; i < stops.size(); i++) {
            Path new_way = findWay(stops.get(i - 1), stops.get(i));
            settlements.addAll(new_way.path_nodes);
            roads.addAll(new_way.path_edges);
        }

        return new Route(settlements, roads);
    }

    public List<BaseSettlement> getSettlements() {
        return this.nodes;
    }

    public List<BaseRoad> getRoads() {
        List<BaseRoad> roads = new ArrayList<>();
        for (Map.Entry<BaseSettlement, List<BaseRoad>> entry : edges.entrySet()) {
            roads.addAll(entry.getValue());
        }
        return roads;
    }
}

public class TransportCompany {
    private TransportNetwork network;
    private List<Route> routes;
    private List<CargoVehicle> cargoVehicles;
    private List<PassengerVehicle> passengerVehicles;
    private Map<Route, List<BaseVehicle>> activeRoutes;

    protected TransportCompany() {
        network = new TransportNetwork();
        routes = new ArrayList<>();
        cargoVehicles = new ArrayList<>();
        passengerVehicles = new ArrayList<>();
        activeRoutes = new HashMap<>();
    }

    public void addSettlement(BaseSettlement settlement) {
        network.addSettlement(settlement);
    }

    public void addRoad(BaseRoad road) {
        addRoad(road, false);
    }

    public void addRoad(BaseRoad road, boolean two_way) {
        network.addRoad(road);
        if (two_way) {
            network.addRoad(road.flip());
        }
    }

    public int addRoute(Route route) {
        if (route != null) {
            if (!routes.contains(route)) {
                routes.add(route);
                activeRoutes.put(route, new ArrayList<>());
            }
            return route.getId();
        }
        return -1;
    }

    public void addVehicle(CargoVehicle vehicle) {
        if (!cargoVehicles.contains(vehicle)) {
            cargoVehicles.add(vehicle);
        }
    }

    public void addVehicle(PassengerVehicle vehicle) {
        if (!passengerVehicles.contains(vehicle)) {
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

    public void putVehicleOnRoute(BaseVehicle vehicle, Route route) {
        if (vehicle == null || route == null) {
            // Naspa
            return;
        }
        addRoute(route);
        addVehicle(vehicle);

        if (!activeRoutes.get(route).contains(vehicle)) {
            activeRoutes.get(route).add(vehicle);
        }
    }

    public Route findRoute(List<BaseSettlement> stops) {
        return network.findRoute(stops);
    }

    protected BaseSettlement findSettlement(String name) {
        return network.findSettlement(name);
    }

    protected BaseVehicle findVehicle(String licencePlate) {
        for (BaseVehicle vehicle : passengerVehicles) {
            if (vehicle.getLicencePlate().equals(licencePlate)) {
                return vehicle;
            }
        }
        for (BaseVehicle vehicle: cargoVehicles) {
            if (vehicle.getLicencePlate().equals(licencePlate)) {
                return vehicle;
            }
        }
        return null;
    }

    protected Route findRouteById(int id) {
        for (Route route : routes) {
            if (route.getId() == id) {
                return route;
            }
        }
        return null;
    }

    protected List<BaseSettlement> getSettlements() {
        return network.getSettlements();
    }

    protected List<BaseRoad> getRoads() {
        return network.getRoads();
    }

    protected List<BaseVehicle> getVehicles() {
        List<BaseVehicle> answer = new ArrayList<>(passengerVehicles);
        answer.addAll(cargoVehicles);
        return answer;
    }

    protected List<Route> getRoutes() {
        return routes;
    }

    protected Map<Route, List<BaseVehicle>> getActiveRoutes() { return activeRoutes; }

    public List<BaseVehicle> getVehiclesOnRoute(Route route) {
        return activeRoutes.get(route);
    }
}
