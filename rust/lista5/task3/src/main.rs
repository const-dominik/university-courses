fn main() {}

fn reverse_words(str: &str) -> String {
    //we can ignore cases with double or more spaces - splitting that string will
    //result in extra empty strings in resulting vector, proper amount of spaces will be added while joining
    str.split(" ")
        .map(|x| x.chars().rev().collect())
        .collect::<Vec<String>>()
        .join(" ")
}

#[test]
fn test1() {
    assert_eq!(
        reverse_words("The quick brown fox jumps over the lazy dog."),
        "ehT kciuq nworb xof spmuj revo eht yzal .god"
    );
}
#[test]
fn test2() {
    assert_eq!(reverse_words("apple"), "elppa");
}
#[test]
fn test3() {
    assert_eq!(reverse_words("a b c d"), "a b c d");
}
#[test]
fn test4() {
    assert_eq!(
        reverse_words("double  spaced  words"),
        "elbuod  decaps  sdrow"
    );
}
#[test]
fn test5() {
    assert_eq!(reverse_words(""), "");
}
