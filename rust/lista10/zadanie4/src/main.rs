fn main() {}

fn encode(msg: String, n: i32) -> Vec<i32> {
    let key = n.to_string();
    let key_len = key.len();
    let mut i: usize = 0;

    let mut alphabet: Vec<char> = Vec::new();
    let mut res: Vec<i32> = Vec::new();

    for letter in 'a'..='z' {
        alphabet.push(letter);
    }

    for letter in msg.chars() {
        let index = alphabet.iter().position(|&x| x == letter).unwrap();
        res.push(
            (index + 1) as i32 + key.chars().nth(i % key_len).unwrap().to_digit(10).unwrap() as i32,
        );
        i += 1;
    }

    res
}

#[test]
fn fixed_tests1() {
    assert_eq!(encode("scout".to_string(), 1939), vec![20, 12, 18, 30, 21]);
}

#[test]
fn fixed_tests2() {
    assert_eq!(
        encode("masterpiece".to_string(), 1939),
        vec![14, 10, 22, 29, 6, 27, 19, 18, 6, 12, 8]
    );
}

#[test]
fn fixed_tests3() {
    assert_eq!(
        encode("tescik".to_string(), 1939),
        vec![21, 14, 22, 12, 10, 20]
    );
}

#[test]
fn fixed_tests4() {
    assert_eq!(
        encode("dominik".to_string(), 1939),
        vec![5, 24, 16, 18, 15, 18, 14]
    );
}

#[test]
fn fixed_tests5() {
    assert_eq!(encode("rust".to_string(), 1939), vec![19, 30, 22, 29]);
}
