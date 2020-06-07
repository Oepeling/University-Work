package data.roads;

import data.settlements.BaseSettlement;

public class DistrictRoad extends BaseRoad {
    DistrictRoad(BaseSettlement from, BaseSettlement to) {
        super(from, to);
    }

    DistrictRoad(BaseSettlement from, BaseSettlement to, int length) {
        super(from, to, length);
    }

    public DistrictRoad(String name, BaseSettlement from, BaseSettlement to, int length) {
        super(name, from, to, length);
    }

    @Override
    public BaseRoad flip() {
        return new DistrictRoad(super.name, super.to, super.from, super.length);
    }
}
