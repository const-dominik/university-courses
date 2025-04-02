fn main() {}

fn string_to_number(s: &str) -> i32 {
    return s.parse::<i32>().unwrap();
}

#[test]
fn str_to_num() {
    assert_eq!(string_to_number("1234"), 1234);
    assert_eq!(string_to_number("605"), 605);
    assert_eq!(string_to_number("1405"), 1405);
    assert_eq!(string_to_number("-7"), -7);
    assert_eq!(string_to_number("-20"), -20);
}
