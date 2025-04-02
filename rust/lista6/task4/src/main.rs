fn main() {
    println!("Hello, world!");
}

fn capitalize(s: &str) -> Vec<String> {
    let mut result = vec!["".to_string(); 2];

    for (i, c) in s.chars().enumerate() {
        if i % 2 == 0 {
            result[0].push_str(&c.to_uppercase().to_string());
            result[1].push_str(&c.to_string());
        } else {
            result[1].push_str(&c.to_uppercase().to_string());
            result[0].push_str(&c.to_string());
        }
    }

    result
}

#[test]
fn test1() {
    assert_eq!(capitalize("abcdef"), ["AbCdEf", "aBcDeF"]);
}

#[test]
fn test2() {
    assert_eq!(capitalize("codewars"), ["CoDeWaRs", "cOdEwArS"]);
}

#[test]
fn test3() {
    assert_eq!(capitalize("abracadabra"), ["AbRaCaDaBrA", "aBrAcAdAbRa"]);
}

#[test]
fn test4() {
    assert_eq!(capitalize("codewarriors"), ["CoDeWaRrIoRs", "cOdEwArRiOrS"]);
}

#[test]
fn test5() {
    assert_eq!(capitalize("tescik"), ["TeScIk", "tEsCiK"]);
}
