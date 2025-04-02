fn main() {}

struct Cipher {
    map1: Vec<char>,
    map2: Vec<char>,
}

impl Cipher {
    fn new(map1: &str, map2: &str) -> Cipher {
        Cipher {
            map1: map1.chars().collect(),
            map2: map2.chars().collect(),
        }
    }

    fn encode(&self, string: &str) -> String {
        let encoded_string: String = string
            .chars()
            .map(|c| {
                if let Some(pos) = self.map1.iter().position(|&x| x == c) {
                    self.map2[pos]
                } else {
                    c
                }
            })
            .collect();
        encoded_string
    }

    fn decode(&self, string: &str) -> String {
        let decoded_string: String = string
            .chars()
            .map(|c| {
                if let Some(pos) = self.map2.iter().position(|&x| x == c) {
                    self.map1[pos]
                } else {
                    c
                }
            })
            .collect();
        decoded_string
    }
}

#[test]
fn examples() {
    let map1 = "abcdefghijklmnopqrstuvwxyz";
    let map2 = "etaoinshrdlucmfwypvbgkjqxz";

    let cipher = Cipher::new(map1, map2);

    assert_eq!(cipher.encode("abc"), "eta");
    assert_eq!(cipher.encode("xyz"), "qxz");
    assert_eq!(cipher.decode("eirfg"), "aeiou");
    assert_eq!(cipher.decode("erlang"), "aikcfu");
    assert_eq!(cipher.decode(""), "");
}
