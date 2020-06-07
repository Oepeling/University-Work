package data.roads;

import data.settlements.BaseSettlement;

public class StateHighway extends BaseRoad {
    StateHighway(BaseSettlement from, BaseSettlement to) {
        super(from, to);
    }

    StateHighway(BaseSettlement from, BaseSettlement to, int length) {
        super(from, to, length);
    }

    public StateHighway(String name, BaseSettlement from, BaseSettlement to, int length) {
        super(name, from, to, length);
    }

    @Override
    public BaseRoad flip() {
        return new StateHighway(super.name, super.to, super.from, super.length);
    }
}
