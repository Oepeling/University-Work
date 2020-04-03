public class TransportCompanyService extends TransportCompany {
    public void addSettlement(String name, SettlementType type) {
        addSettlement(name, type, 0);
    }

    public void addSettlement(String name, SettlementType type, int population) {
        BaseSettlement toAdd;
        if (type == SettlementType.Hamlet) {
            toAdd = new Hamlet(name, population);
        } else if (type == SettlementType.Village) {
            toAdd = new Village(name, population);
        } else if (type == SettlementType.Town) {
            toAdd = new Town(name, population);
        } else {
            toAdd = new City(name, population);
        }
        super.addSettlement(toAdd);
    }

    public void addRoad(String name, String from, String to, RoadType type) {
        addRoad(name, from, to, type, 0);
    }

    public void addRoad(String from, String to, RoadType type) {
        addRoad("", from, to, type, 0);
    }

    public void addRoad(String from, String to, RoadType type, int length) {
        addRoad("", from, to, type, length);
    }

    public void addRoad(String name, String from, String to, RoadType type, int length) {
        BaseSettlement fromS = super.findSettlement(from);
        BaseSettlement toS = super.findSettlement(to);
        if (fromS == null || toS == null) {
            // Naspa
            return;
        }

        BaseRoad toAdd;
        if (type == RoadType.RuralRoad) {
            toAdd = new RuralRoad(name, fromS, toS, length);
        } else if (type == RoadType.DistrictRoad) {
            toAdd = new DistrictRoad(name, fromS, toS, length);
        } else if (type == RoadType.StateHighway) {
            toAdd = new StateHighway(name, fromS, toS, length);
        } else {
            toAdd = new NationalHighway(name, fromS, toS, length);
        }

        super.addRoad(toAdd);
        toAdd.flip();
        super.addRoad(toAdd);
    }

    public enum SettlementType {Hamlet, Village, Town, City}

    public enum RoadType {RuralRoad, DistrictRoad, StateHighway, NationalHighway, TruckOnly}
}
