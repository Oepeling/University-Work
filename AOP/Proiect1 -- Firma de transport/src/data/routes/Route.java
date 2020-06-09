package data.routes;

import data.roads.BaseRoad;
import data.settlements.BaseSettlement;

import java.util.List;

public class Route {
    private static int index;
    private int id;
    protected List<BaseSettlement> settlements;
    protected List<BaseRoad> roads;

    Route() {
        id = index;
        index++;
    }

    public Route(List<BaseSettlement> settlements_,
                 List<BaseRoad> roads_) {
        id = index;
        index++;
        settlements = settlements_;
        roads = roads_;
    }

    @Override
    public void finalize() {
        index--;
    }

    public int getId() {
        return id;
    }

    public List<BaseSettlement> getSettlements() {
        return settlements;
    }

    @Override
    public String toString() {
        String s = "ID: " + getId() + "; Stops: ";
        for (BaseSettlement settlement : getSettlements()) {
            s = s + settlement.getName() + ", ";
        }
        return s.substring(0, s.length() - 2);
    }
}
