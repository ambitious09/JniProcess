package com.lhh.jniprocess;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

/**
 * Created by 刘会华 on 2017/9/11.
 */
public class CalculterTest {
    @Before
    public void setUp() throws Exception {
        System.out.println("Before");
    }

    @After
    public void tearDown() throws Exception {
        System.out.println("After");
    }

    @Test
    public void add() throws Exception {
        System.out.println("Test");
        Calculter calculter=new Calculter();
        int add = calculter.add(3, 2);
        Assert.assertEquals(5,add);
    }

}