package main;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.*;

class HuffmanTreeTest {
    @Test
    void getCodeTable() {
        Map<Character, Integer> input = new HashMap<>();
        input.put('e', 120);
        input.put('d', 42);
        input.put('c', 32);
        input.put('m', 24);
        input.put('k', 7);
        input.put('l', 42);
        input.put('u', 37);
        input.put('z', 2);

        HuffmanTree huffmanTree = new HuffmanTree();
        huffmanTree.Store(input);
        Map<Character, String> expected = new HashMap<>();
        expected.put('e', "0");
        expected.put('d', "110");
        expected.put('c', "1110");
        expected.put('m', "11111");
        expected.put('k', "111101");
        expected.put('l', "101");
        expected.put('u', "100");
        expected.put('z', "111100");

        Map<Character, String> actual = huffmanTree.getCodeTable();
        for (Map.Entry<Character, String> entry : expected.entrySet()) {
            assertEquals(entry.getValue(), actual.get(entry.getKey()));
        }
    }

    @Test
    void getDecodeTable() {
    }
}