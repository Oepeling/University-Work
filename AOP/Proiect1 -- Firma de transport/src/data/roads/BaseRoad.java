package data.roads;

import com.sun.xml.internal.rngom.parse.host.Base;
import data.settlements.BaseSettlement;

public abstract class BaseRoad {
    private static int index;
    protected String name;
    protected BaseSettlement from;
    protected BaseSettlement to;
    protected int length;

    BaseRoad(BaseSettlement from, BaseSettlement to) {
        index++;
        name = "";
        this.from = from;
        this.to = to;
        length = 0;
    }

    BaseRoad(BaseSettlement from, BaseSettlement to, int length) {
        index++;
        name = "";
        this.from = from;
        this.to = to;
        this.length = length;
    }

    BaseRoad(String name, BaseSettlement from, BaseSettlement to, int length) {
        index++;
        this.name = name;
        this.from = from;
        this.to = to;
        this.length = length;
    }

    @Override
    public void finalize() {
        index--;
    }

    public int getLength() {
        return length;
    }

    public void setLength(int length) {
        this.length = length;
    }

    public BaseSettlement getFrom() {
        return from;
    }

    public void setFrom(BaseSettlement from) {
        this.from = from;
    }

    public BaseSettlement getTo() {
        return to;
    }

    public void setTo(BaseSettlement to) {
        this.to = to;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public BaseRoad flip() {
        return null;
    }

    @Override
    public String toString() {
        return String.format("Name: %s; Type: %s; From: %s; To: %s; Length: %d km",
                getName(),
                getClass().getSimpleName(),
                getFrom().getName(),
                getTo().getName(),
                getLength());
    }
}
