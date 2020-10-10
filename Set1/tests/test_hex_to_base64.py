import unittest

from hex_to_base64 import hex_to_base64

class TextHexToBase64(unittest.TestCase):

    def setUp(self):
        pass

    def test_cryptopals_exercise(self):
        init_hex = b'49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d'
        expected = b'SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t'

        self.assertEqual(hex_to_base64(init_hex), expected)

if __name__ == '__main__':
    unittest.main()
