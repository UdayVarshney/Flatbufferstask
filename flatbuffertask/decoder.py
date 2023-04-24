import flatbuffers
from Example.Client import Client
from Example.ClientData import  ClientData
from Example.Person import  Person
from Example.Group import  Group

def decode_client(buf):
    client = Client.GetRootAs(buf, 0)

    # Decode the client data based on the client data type
    client_data = client.ClientData()
    if client_data is None:
        return None

    client_data_type = client.ClientDataType()
    result = {}

    if client_data_type == ClientData.Person:
        person = Person()
        person.Init(client_data.Bytes, client_data.Pos)
        result = {
            'type': 'person',
            'name': person.Name().decode(),
            'age': person.Age(),
            'weight': person.Weight(),
            'gender': person.Gender().decode()
        }

    elif client_data_type == ClientData.Group:
        group = Group()
        group.Init(client_data.Bytes, client_data.Pos)
        result = {
            'type': 'group',
            'name': group.Name().decode(),
            'average_age': group.AverageAge(),
            'average_weight': group.AverageWeight(),
            'members': [group.Members(i).decode() for i in range(group.MembersLength())],
        }

    return result


with open('../flatbuffertask/fb_bytes.bin', 'rb') as f:
    buf = f.read()  
    while len(buf) > 0:
        int_val = int.from_bytes(buf[:4], "little")
        client_info = decode_client(buf[4:int_val+4])
        if client_info is not None:
            if client_info['type'] == 'person':
                persons=[]
                persons.append(client_info['name'])
                persons.append(client_info['age'])
                persons.append(client_info['weight'])
                persons.append(client_info['gender'])
                print(persons)
            if client_info['type'] == 'group':
                group=[]
                members=[]
                group.append(client_info['name'])
                group.append(client_info['average_age'])
                group.append(client_info['average_weight'])
                for member in client_info['members']:
                    members.append(member)
                group.append(members)
                print(group)
        else:
            print("Error decoding client")
        buf=buf[int_val+4:]
            
