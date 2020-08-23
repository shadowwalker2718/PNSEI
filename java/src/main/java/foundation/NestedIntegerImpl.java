package foundation;

import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;

public class NestedIntegerImpl implements NestedInteger{
    private Integer i = 0;
    private boolean isInt = false;
    private List<NestedInteger> ln = new ArrayList<>();

    public NestedIntegerImpl setInteger(int i){
        i = i;
        isInt = true;
        return this;
    }

    public NestedIntegerImpl addInteger(int i){
        isInt = false;
        NestedIntegerImpl nii = new NestedIntegerImpl();
        nii.setInteger(i);
        ln.add(nii);
        return this;
    }

    @Override
    public boolean isInteger() {
        return isInt;
    }

    @Override
    public Integer getInteger() {
        if (isInteger())
            return i;
        throw new NoSuchElementException();
    }

    @Override
    public List<NestedInteger> getList() {
        return ln;
    }
}
