Initial RefCountTable:
Doe, John E 123-45-6789 20892=>2
Doe, Jane F 987-65-4321 20892=>1

Doe, John E 123-45-6789 20892
Doe, Jane F 987-65-4321 20892
Doe, John E 123-45-6789 20892

Doe, John E 123-45-6789 20892

RefCountTable after cp2 = cp1:
Doe, John E 123-45-6789 20892=>3

RefCountTable after delete cpp:
Doe, John E 123-45-6789 20892=>2
