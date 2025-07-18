import unittest

from HashTable import HashTable

class TestHashTable(unittest.TestCase):
    def test_insert_and_search(self):
        ht = HashTable()
        ht.insert("key1")
        ht.insert("key2")
        ht.insert("key3")

        self.assertTrue("key1" in ht)
        self.assertTrue("key2" in ht)
        self.assertTrue("key3" in ht)

        pos1 = ht.search("key1")
        pos2 = ht.search("key2")
        pos3 = ht.search("key3")

        self.assertNotEqual(pos1, [0, 0])
        self.assertNotEqual(pos2, [0, 0])
        self.assertNotEqual(pos3, [0, 0])

    def test_no_duplicate_insert(self):
        ht = HashTable()
        ht.insert("key")
        initial_length = len(ht)
        ht.insert("key")
        self.assertEqual(len(ht), initial_length)

        self.assertTrue("key" in ht)
        pos = ht.search("key")
        self.assertNotEqual(pos, [0, 0])

    def test_remove(self):
        ht = HashTable()
        ht.insert("key1")
        ht.insert("key2")
        ht.remove("key1")


        self.assertEqual(ht.search("key1"), [0, 0])

        self.assertTrue("key2" in ht)
        pos2 = ht.search("key2")
        self.assertNotEqual(pos2, [0, 0])

        with self.assertRaises(KeyError):
            ht.remove("key1")


if __name__ == '__main__':
    unittest.main()