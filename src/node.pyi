from typing import List, Optional

class Node:
    def __init__(self, type: str, sourcepos: List[List[int]]) -> None: ...
    
    def append_child(self, child: "Node") -> None: ...
    def prepend_child(self, child: "Node") -> None: ...
    def unlink(self) -> None: ...
    def insert_after(self, sibling: "Node") -> None: ...
    def insert_before(self, sibling: "Node") -> None: ...
    def walker(self): ...
    
    type: str
    sourcepos: List[List[int]]
    literal: Optional[str]
    destination: Optional[str]
    title: Optional[str]
    info: Optional[str]
    level: int

    @property
    def first_child(self) -> Optional["Node"]: ...
    @property
    def last_child(self) -> Optional["Node"]: ...
    @property
    def next(self) -> Optional["Node"]: ...
    @property
    def prev(self) -> Optional["Node"]: ...
    @property
    def parent(self) -> Optional["Node"]: ...
    @property
    def container(self) -> bool: ...
