
from HashTable import HashTable


class SymTblConst:
    def __init__(self):
        self.sym_tbl_const = HashTable()

    def insert_const(self, key):
        self.sym_tbl_const.insert(key)

    def get_const(self,key):
        return self.sym_tbl_const.search(key)

    def remove_const(self, key):
        return self.sym_tbl_const.remove(key)

    def print_table(self):
        return self.sym_tbl_const.print_all()

    def get_table(self):
        return self.sym_tbl_const.table


class SymTblIdentifier:
    def __init__(self):
        self.sym_tbl_identifier = HashTable()

    def insert_identifier(self, key):
        self.sym_tbl_identifier.insert(key)

    def get_identifier(self, key):
        return self.sym_tbl_identifier.search(key)

    def remove_identifier(self, key):
        return self.sym_tbl_identifier.remove(key)

    def print_table(self):
        return self.sym_tbl_identifier.print_all()

    def get_table(self):
        return self.sym_tbl_identifier.table
