fn main() {
    number(&[(10, 0), (3, 5), (5, 8)]);
}

fn number(bus_stops: &[(i32, i32)]) -> i32 {
    let mut people = 0;
    for &(on, off) in bus_stops {
        people += on - off
    }

    people
}

#[test]
fn test_1() {
    assert_eq!(number(&[(10, 0), (3, 5), (5, 8)]), 5);
}

#[test]
fn test_2() {
    assert_eq!(
        number(&[(3, 0), (9, 1), (4, 10), (12, 2), (6, 1), (7, 10)]),
        17
    );
}

#[test]
fn test_3() {
    assert_eq!(
        number(&[(3, 0), (9, 1), (4, 8), (12, 2), (6, 1), (7, 8)]),
        21
    );
}

#[test]
fn test_4() {
    assert_eq!(number(&[]), 0);
}
#[test]
fn test_5() {
    assert_eq!(number(&[(3, 3)]), 0);
}
