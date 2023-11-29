package main;

import java.util.*;

public class HuffmanTree {
    /****************************************************************
     *                 public methods and properties                *
     ****************************************************************/

    public HuffmanTree() {
        this.codeTable = new HashMap<>();
        this.decodeTable = new HashMap<>();
    }

    /**
     * Stores the frequency table into the Huffman tree.
     * Key is the character, value is the frequency.
     *
     * @param frequencyTable the frequency table
     */
    public void Store(Map<Character, Integer> frequencyTable) {
        this.frequencyTable = frequencyTable;
        huffmanBuild();
    }

    /**
     * Returns the frequency table.
     * Key is the character, value is the frequency.
     *
     * @return the frequency table
     */
    public Map<Character, String> getCodeTable() {
        return codeTable;
    }

    /**
     * Returns the decode table.
     * Key is the code, value is the character.
     *
     * @return the decode table
     */
    public Map<String, Character> getDecodeTable() {
        return decodeTable;
    }

    /****************************************************************
     *                private methods and properties                *
     ****************************************************************/
    class HuffmanNode {
        private final char character;
        private final int frequency;
        private final HuffmanNode left;
        private final HuffmanNode right;

        HuffmanNode(char character, int frequency) {
            this.character = character;
            this.frequency = frequency;
            this.left = null;
            this.right = null;
        }

        HuffmanNode(HuffmanNode left, HuffmanNode right) {
            this.character = '\0';
            this.frequency = left.frequency + right.frequency;
            this.left = left;
            this.right = right;
        }
    }

    private Map<Character, Integer> frequencyTable;
    private final Map<Character, String> codeTable;
    private final Map<String, Character> decodeTable;

    private void huffmanBuild() {
        Comparator<HuffmanNode> comparator = new Comparator<>() {
            @Override
            public int compare(HuffmanNode o1, HuffmanNode o2) {
                return o1.frequency - o2.frequency;
            }
        };
        MinPQ<HuffmanNode> minPQ = new MinPQ<>(comparator);

        // Insert all the nodes into the priority queue.
        for (Map.Entry<Character, Integer> entry : frequencyTable.entrySet()) {
            HuffmanNode node = new HuffmanNode(entry.getKey(), entry.getValue());
            minPQ.insert(node);
        }

        // Build the Huffman tree.
        while (minPQ.size() > 1) {
            HuffmanNode left = minPQ.delMin();
            HuffmanNode right = minPQ.delMin();
            HuffmanNode node = new HuffmanNode(left, right);
            minPQ.insert(node);
        }

        // Traverse the Huffman tree to build the code table.
        huffmanCode(minPQ.delMin());
    }

    // Traverse the Huffman tree to build the code table.
    private void huffmanCode(HuffmanNode root) {
        huffmanCode(root, "");
    }

    // Helper function for huffmanCode(HuffmanNode root).
    private void huffmanCode(HuffmanNode root, String code) {
        // Base case.
        if (root.left == null && root.right == null) {
            codeTable.put(root.character, code);
            decodeTable.put(code, root.character);
            return;
        }

        // Recursive case.
        huffmanCode(root.left, code + "0");
        huffmanCode(root.right, code + "1");
    }
}
