const state = {
    name: '',
    roles: []
}

const mutations = {
    SET_NAME: (state, name) => {
        state.name = name
    },
    SET_ROLES: (state, roles) => {
        state.roles = roles
    }
}