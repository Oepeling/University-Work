package data.roads;

import data.settlements.BaseSettlement;

public class NationalHighway extends BaseRoad {
    NationalHighway(BaseSettlement from, BaseSettlement to) {
        super(from, to);
    }

    NationalHighway(BaseSettlement from, BaseSettlement to, int length) {
        super(from, to, length);
    }

    public NationalHighway(String name, BaseSettlement from, BaseSettlement to, int length) {
        super(name, from, to, length);
    }

    @Override
    public BaseRoad flip() {
        return new NationalHighway(super.name, super.to, super.from, super.length);
    }
}
