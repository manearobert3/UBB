class Domain:
    def __init__(self, real_part, imag_part):
        self.__real_part = real_part
        self.__imag_part = imag_part

    def get_real(self):
        return self.__real_part

    def get_imag(self):
        return self.__imag_part


    def set_real(self,real):
        self.__real_part = real

    def set_name(self, imag):
        self.__imag_part = imag


    def __str__(self):
        return f"{self.__real_part} + {self.__imag_part}i"



