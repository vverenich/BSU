package com.verenich.parser;

import java.util.List;

import com.verenich.Entities.Vegetable;
import com.verenich.exception.ParserException;

public interface VegetableParser {
    List<Vegetable> parse(String fileName) throws ParserException;
}
