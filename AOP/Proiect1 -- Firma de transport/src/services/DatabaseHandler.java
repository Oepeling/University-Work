package services;

import data.roads.BaseRoad;
import data.settlements.BaseSettlement;
import data.vehicles.BaseVehicle;
import data.routes.Route;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DatabaseHandler {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/aop?serverTimezone=UTC";
    private static final String USER = "root";
    private static final String PASS = "MyStrongPass";
    private Statement statement;

    public DatabaseHandler() throws SQLException {
        Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
        statement = connection.createStatement();
    }

    public boolean existsTable(String tableName) throws SQLException {
        String sqlQuery = String.format("select count(*) from information_schema.TABLES  where table_name = '%s';",
                tableName);
        ResultSet resultSet = statement.executeQuery(sqlQuery);
        resultSet.next();
        int size = resultSet.getInt(1);
        return size != 0;
    }

    public void createSettlementsTable(TransportCompanyService service) throws SQLException {
        List<BaseSettlement> settlements = service.getSettlements();
        String sqlQuery = "create table settlements (name varchar(20), size int, type varchar(20));";
        statement.execute(sqlQuery);

        for (BaseSettlement settlement : settlements) {
            sqlQuery = String.format("insert into settlements values( '%s', %d, '%s' );",
                    settlement.getName(),
                    settlement.getSize(),
                    settlement.getClass().getSimpleName());
            statement.execute(sqlQuery);
        }
    }

    public void readSettlements(TransportCompanyService service) throws SQLException {
        String sqlQuery = "select * from settlements;";
        ResultSet resultSet = statement.executeQuery(sqlQuery);
        while (resultSet.next()) {
            String name = resultSet.getString(1);
            int size = resultSet.getInt(2);
            String type = resultSet.getString(3);
            service.addSettlement(name, type, size);
        }
    }

    public void createRoadsTable(TransportCompanyService service) throws SQLException {
        List<BaseRoad> roads = service.getRoads();
        String sqlQuery = "create table roads (name varchar(20), `from` varchar(20), `to` varchar(20), type varchar(20), length int);";
        statement.execute(sqlQuery);

        for (BaseRoad road : roads) {
            sqlQuery = String.format("insert into roads values( '%s', '%s', '%s', '%s', %d );",
                    road.getName(),
                    road.getFrom().getName(),
                    road.getTo().getName(),
                    road.getClass().getSimpleName(),
                    road.getLength());
            statement.execute(sqlQuery);
        }
    }

    public void readRoads(TransportCompanyService service) throws SQLException {
        String sqlQuery = "select * from roads;";
        ResultSet resultSet = statement.executeQuery(sqlQuery);
        while (resultSet.next()) {
            String name = resultSet.getString(1);
            String from = resultSet.getString(2);
            String to = resultSet.getString(3);
            String type = resultSet.getString(4);
            int length = resultSet.getInt(5);
            service.addRoad(name, from, to, type, length, false);
        }
    }

    public void createVehiclesTable(TransportCompanyService service) throws SQLException {
        List<BaseVehicle> vehicles = service.getVehicles();
        String sqlQuery = "create table vehicles (licence_plate varchar(20), type varchar(20), capacity float, smoking_allowed boolean, animal_friendly boolean);";
        statement.execute(sqlQuery);

        for (BaseVehicle vehicle : vehicles) {
            sqlQuery = String.format("insert into vehicles values( '%s', '%s', %f, %b, %b );",
                    vehicle.getLicencePlate(),
                    vehicle.getClass().getSimpleName(),
                    vehicle.getCapacity(),
                    vehicle.isSmokingAllowed(),
                    vehicle.isAnimalFriendly());
            statement.execute(sqlQuery);
        }
    }

    public void readVehicles(TransportCompanyService service) throws SQLException {
        String sqlQuery = "select * from vehicles;";
        ResultSet resultSet = statement.executeQuery(sqlQuery);
        while (resultSet.next()) {
            String licencePlate = resultSet.getString(1);
            String type = resultSet.getString(2);
            float capacity = resultSet.getFloat(3);
            boolean smokingAllowed = resultSet.getBoolean(4);
            boolean animalFriendly = resultSet.getBoolean(5);
            service.addVehicle(licencePlate, type, capacity, smokingAllowed, animalFriendly);
        }
    }

    public void createRoutesTable(TransportCompanyService service) throws SQLException {
        List<Route> routes = service.getRoutes();
        String sqlQuery = "create table routes (route_id int, position int, name varchar(20))";
        statement.execute(sqlQuery);

        for (Route route : routes) {
            int cnt = 0;
            for (BaseSettlement stop : route.getSettlements()) {
                sqlQuery = String.format("insert into routes values( %d, %d, '%s' );",
                        route.getId(),
                        cnt,
                        stop.getName());
                statement.execute(sqlQuery);
                cnt++;
            }
        }
    }

    public void readRoutes(TransportCompanyService service) throws SQLException {
        String sqlQuery = "select * from routes order by route_id, `position`;";
        ResultSet resultSet = statement.executeQuery(sqlQuery);

        int lastRoute = 0;
        List<String> stops = new ArrayList<>();
        while (resultSet.next()) {
            int routeId = resultSet.getInt(1);
            String stopName = resultSet.getString(3);

            if (routeId != lastRoute) {
                service.addTransportRoute(stops);
                stops.clear();
            }

            stops.add(stopName);
        }

        service.addTransportRoute(stops);
    }

    public void createRouteVehicleTable(TransportCompanyService service) throws SQLException {
        String sqlQuery = "create table routes_vehicles (route_id int, vehicle_licence_plate varchar(20));";
        statement.execute(sqlQuery);

        List<Route> routes = service.getRoutes();
        for (Route route : routes) {
            List<BaseVehicle> vehicles = service.getVehiclesOnRoute(route);
            for (BaseVehicle vehicle : vehicles) {
                sqlQuery = String.format("insert into routes_vehicles values( %d, '%s' );",
                        route.getId(),
                        vehicle.getLicencePlate());
                statement.execute(sqlQuery);
            }
        }
    }

    public void readRouteVehicle(TransportCompanyService service) throws SQLException {
        String sqlQuery = "select * from routes_vehicles;";
        ResultSet resultSet = statement.executeQuery(sqlQuery);
        while (resultSet.next()) {
            int route_id = resultSet.getInt(1);
            String vehicleLicencePlate = resultSet.getString(2);
            service.putVehicleOnRoute(vehicleLicencePlate, route_id);
        }
    }

    public void commit() {
        try {
            String sqlQuery = "commit";
            statement.execute(sqlQuery);
        } catch (SQLException error) {
            error.printStackTrace();
        }
    }

    public void rollback() {
        try {
            String sqlQuery = "rollback";
            statement.execute(sqlQuery);
        } catch (SQLException error) {
            error.printStackTrace();
        }
    }

    public void dropTable(String tableName) {
        try {
            if (existsTable(tableName)) {
                String sqlQuery = "drop table " + tableName + ";";
                statement.execute(sqlQuery);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
