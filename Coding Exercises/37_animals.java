//Animal shelter queue

import java.util.LinkedList;

class Solution{
	public static void main(String[] args){
		AnimalQueue queue = new AnimalQueue();
		Dog toby = new Dog("toby");
		Dog boby = new Dog("boby");
		Dog doby = new Dog("doby");
		Dog loby = new Dog("loby");
		Dog moby = new Dog("moby");
		Cat evil = new Cat("evil");
		
		queue.enqueue(toby);
		queue.enqueue(boby);
		queue.enqueue(doby);
		queue.enqueue(loby);
		queue.enqueue(moby);
		queue.enqueue(evil);
		
		System.out.println(queue.dequeueAny().name);
		System.out.println(queue.dequeueCats().name);
				System.out.println(queue.dequeueAny().name);

		
		
	}
}


abstract class Animal{
	private int order;
	protected String name;
	public Animal(String n){
		this.name = n;
	}
	
	public void setOrder(int ord){
		this.order = ord;
	}
	
	public int getOrder(){
		return this.order;
	}
	
	public boolean isOlderThan(Animal a){
		return this.order < a.getOrder();
	}
}

class AnimalQueue {
	LinkedList<Dog> dogs = new LinkedList<Dog>();
	LinkedList<Cat> cats = new LinkedList<Cat>();
	private int order = 0;
	
	public void enqueue(Animal a){
		a.setOrder(order);
		order++;
		if(a instanceof Dog) dogs.addLast((Dog) a);
		else if(a instanceof Cat) cats.addLast((Cat) a);
	}
	public Animal dequeueAny(){
		if(dogs.size() == 0){
			return dequeueCats();
		} else if (cats.size() == 0){
			return dequeueDogs();
		}
		
		Dog dog = dogs.peek();
		Cat cat = cats.peek();
		if(dog.isOlderThan(cat)) {
			return dequeueDogs();
		} else {
			return dequeueCats();
		}
	 }
	 
	 public Dog dequeueDogs(){
		return dogs.poll();
	 }
	 
	 public Cat dequeueCats(){
		return cats.poll();
	 }
}

class Dog extends Animal {
	public Dog(String n){super(n);}
}

class Cat extends Animal {
	public Cat(String n){super(n);}
}