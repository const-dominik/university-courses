fn main() {}

pub fn range_extraction(a: &[i32]) -> String {
    let mut ranges: Vec<String> = vec![];
    let mut begin = a[0];
    let mut end = a[0];

    for num in a.iter().skip(1) {
        if *num == end + 1 {
            end = *num;
        } else {
            ranges.push(make_range(begin, end));
            begin = *num;
            end = *num;
        }
    }
    ranges.push(make_range(begin, end));

    ranges.join(",")
}

fn make_range(begin: i32, end: i32) -> String {
    if begin == end {
        begin.to_string()
    } else if end - begin == 1 {
        format!("{},{}", begin, end)
    } else {
        format!("{}-{}", begin, end)
    }
}

#[test]
fn test1() {
    assert_eq!(
        range_extraction(&[-6, -3, -2, -1, 0, 1, 3, 4, 5, 7, 8, 9, 10, 11, 14, 15, 17, 18, 19, 20]),
        "-6,-3-1,3-5,7-11,14,15,17-20"
    );
}
#[test]
fn test2() {
    assert_eq!(
        range_extraction(&[-3, -2, -1, 2, 10, 15, 16, 18, 19, 20]),
        "-3--1,2,10,15,16,18-20"
    );
}
#[test]
fn test3() {
    assert_eq!(range_extraction(&[-2, -1, 0, 1, 2]), "-2-2");
}
#[test]
fn test4() {
    assert_eq!(range_extraction(&[1, 2, 3]), "1-3");
}
#[test]
fn test5() {
    assert_eq!(range_extraction(&[0]), "0");
}
