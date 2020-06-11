import services.TransportCompanyService;

//import java.util.*;

public class Main {
    public static void main(String[] args) {
        TransportCompanyService tcs = TransportCompanyService.getInstance();
//
//        tcs.addSettlement("Bucuresti", "City", 3000000);
//        tcs.addSettlement("Cluj-Napoca", "City", 1000000);
//        tcs.addSettlement("Otopeni", "Town", 10000);
//
//        tcs.addRoad("A4", "Bucuresti", "Cluj-Napoca", "NationalHighway", 450);
//        tcs.addRoad("Otopeni", "Bucuresti", "DistrictRoad", 20);
//
//        List<String> ends = new ArrayList<>();
//        ends.add("Cluj-Napoca");
//        ends.add("Otopeni");
//        int routeId = tcs.addTransportRoute(ends);
//
//        tcs.addVehicle("B-45-AOP", "Cab", 3);
//
//        tcs.putVehicleOnRoute("B-45-AOP", routeId);
//        tcs.addVehicle("IF-46-AOP", "Truck", 3);

        tcs.master();
    }
}
